clear; close all; tic

%% import sim input
simFile = fileread("inputs/sim.json");
simData = jsondecode(simFile);

spacecraftFile = fileread("inputs/spacecraft.json");
spacecraftData = jsondecode(spacecraftFile);

earthFile = fileread("inputs/earth.json");
earthData = jsondecode(earthFile);

startTime   = 0.0;
endTime     = simData.simRunTime;
dt          = simData.RK4.timeStep;

year = simData.epoch.year;
month = simData.epoch.month;
day = simData.epoch.day;
utc0 = simData.epoch.utc;

xp = earthData.xp;
yp = earthData.yp;

RofBwrtCexpI_0 = spacecraftData.Spacecraft.initialState.RofBwrtCexpI;
VofBwrtIexpI_0 = spacecraftData.Spacecraft.initialState.VofBwrtIexpI;

opts = Const.propOpts();
opts.J2 = spacecraftData.Spacecraft.dynamics.J2;
opts.J3 = spacecraftData.Spacecraft.dynamics.J3;
opts.J4 = spacecraftData.Spacecraft.dynamics.J4;
opts.epoch = [year, month, day, utc0];
opts.xp = xp;
opts.yp = yp;

%% import sim output
T = readtable("outputs/Spacecraft.csv");
time = T.Time;
RofBwrtCexpI = [T.RofBwrtCexpI_1, T.RofBwrtCexpI_2, T.RofBwrtCexpI_3]';
VofBwrtIexpI = [T.VofBwrtIexpI_1, T.VofBwrtIexpI_2, T.VofBwrtIexpI_3]';
RofBwrtCexpE = [T.RofBwrtCexpE_1, T.RofBwrtCexpE_2, T.RofBwrtCexpE_3]';
VofBwrtIexpE = [T.VofBwrtIexpE_1, T.VofBwrtIexpE_2, T.VofBwrtIexpE_3]';
VofBwrtEexpE = [T.VofBwrtEexpE_1, T.VofBwrtEexpE_2, T.VofBwrtEexpE_3]';
RofBwrtCexpL = [T.RofBwrtCexpL_1, T.RofBwrtCexpL_2, T.RofBwrtCexpL_3]';
VofBwrtIexpL = [T.VofBwrtIexpL_1, T.VofBwrtIexpL_2, T.VofBwrtIexpL_3]';
RofBwrtCexpP = [T.RofBwrtCexpP_1, T.RofBwrtCexpP_2, T.RofBwrtCexpP_3]';
VofBwrtIexpP = [T.VofBwrtIexpP_1, T.VofBwrtIexpP_2, T.VofBwrtIexpP_3]';

HofBwrtCexpI = [T.HofBwrtCexpI_1, T.HofBwrtCexpI_2, T.HofBwrtCexpI_3]';
NofBwrtCexpIhat = [T.NofBwrtCexpIhat_1, T.NofBwrtCexpIhat_2, T.NofBwrtCexpIhat_3]';

a = T.a';
ecc = T.ecc';
inc = T.inc';
raan = T.raan';
aop = T.aop';
ta = T.ta';

aol = T.aol';
p = T.p';
b = T.b';
Rp = T.Rp';
Ra = T.Ra';
E = T.E';
M = T.M';
n = T.n';
P = T.P';
energy = T.energy';
fpa = T.fpa';

T = readtable("outputs/Earth.csv");
gmst = T.gmst';
gast = T.gast';

%% compare against ode45
x0_ECI = [RofBwrtCexpI_0; VofBwrtIexpI_0];
tspan = startTime:dt:endTime;
[t, x_ECI] = ode45(@(t, state) propagator(t, state, opts), tspan, x0_ECI, Const.odeOpts);
x_ECI = x_ECI';

%% get all other state parameters and representations
x_OE = zeros(6,length(t));
x_LVLH = zeros(6,length(t));
x_ECEF = zeros(6,length(t));
x_Peri = zeros(6,length(t));
E_mat = zeros(1,length(t));
M_mat = zeros(1,length(t));
p_mat = zeros(1,length(t));
h_mat = zeros(3,length(t));
hmag_mat = zeros(1,length(t));
nhat_mat = zeros(3,length(t));
energy_mat = zeros(1,length(t));
n_mat = zeros(1,length(t));
P_mat = zeros(1,length(t));
fpa_mat = zeros(1,length(t));
gmst_mat = zeros(1,length(t));

PI = polar_motion(xp, yp);
for k = 1:length(t)
    xk_ECI = x_ECI(:,k);
    [xk_OE, extras] = eci2oe(xk_ECI, Const.muE);
    x_OE(:,k) = xk_OE;

    utck = utc0 + t(k)/3600;
    [~,T1,theta0] = date2jd(year, month, day, utck);
    gmst_mat(1,k) = theta0;

    [NU, dpsi, ep_mean] = nutation(T1);
    PR = precession(T1);
    TH = rot3(theta0 + dpsi*cosd(ep_mean));
    rk_ECEF = PI*TH*NU*PR*xk_ECI(1:3);
    vk_ECEF = PI*TH*NU*PR*xk_ECI(4:6);
    vk_ECEF_ECEF = vk_ECEF - cross(Const.wE, rk_ECEF);
    x_ECEF(:,k) = [rk_ECEF;vk_ECEF];

    E_mat(1,k) = extras.E;
    M_mat(1,k) = extras.M;
    p_mat(1,k) = extras.p;
    h_mat(:,k) = extras.h;
    hmag_mat(1,k) = extras.hmag;
    nhat_mat(:,k) = extras.nhat;

    energy_mat(1,k) = -.5*Const.muE/x_OE(1,k);
    n_mat(1,k) = sqrt(Const.muE/x_OE(1,k)^3);
    P_mat(1,k) = 2*pi/n_mat(1,k);
    fpa_mat(1,k) = atan2d(dot(xk_ECI(1:3), xk_ECI(4:6)), hmag_mat(1,k));
end

%% verify time vectors are equivalent
float_tol = 1e-12;
if any(abs(time - t) > float_tol)
    disp("Simulation and ode45 time vectors are not equivalent.");
end

%% plot results
% Sim vs. Matlab ECI state comparison
figure(1)
sgtitle(sprintf('Sim vs. Matlab\nECI State Errors'))
subplot(3,2,1)
plot(t/3600, (x_ECI(1,:) - RofBwrtCexpI(1,:))*1000, 'LineWidth', 1.5)
hold on
grid on
ylabel('RofBwrtCexpI_1 Error [m]')

subplot(3,2,3)
plot(t/3600, (x_ECI(2,:) - RofBwrtCexpI(2,:))*1000, 'LineWidth', 1.5)
hold on
grid on
ylabel('RofBwrtCexpI_2 Error [m]')

subplot(3,2,5)
plot(t/3600, (x_ECI(3,:) - RofBwrtCexpI(3,:))*1000, 'LineWidth', 1.5)
hold on
grid on
xlabel('Time [hr]')
ylabel('RofBwrtCexpI_3 Error [m]')

subplot(3,2,2)
plot(t/3600, (x_ECI(4,:) - VofBwrtIexpI(1,:))*1000, 'LineWidth', 1.5)
hold on
grid on
ylabel('VofBwrtIexpI_1 Error [m/s]')

subplot(3,2,4)
plot(t/3600, (x_ECI(5,:) - VofBwrtIexpI(2,:))*1000, 'LineWidth', 1.5)
hold on
grid on
ylabel('VofBwrtIexpI_2 Error [m/s]')

subplot(3,2,6)
plot(t/3600, (x_ECI(6,:) - VofBwrtIexpI(3,:))*1000, 'LineWidth', 1.5)
hold on
grid on
xlabel('Time [hr]')
ylabel('VofBwrtIexpI_3 Error [m/s]')


% Sim vs. Matlab ECEF state comparison
figure(2)
sgtitle(sprintf('Sim vs. Matlab\nECEF State Errors'))
subplot(3,2,1)
plot(t/3600, (x_ECEF(1,:) - RofBwrtCexpE(1,:))*1000, 'LineWidth', 1.5)
hold on
grid on
ylabel('RofBwrtCexpE_1 Error [m]')

subplot(3,2,3)
plot(t/3600, (x_ECEF(2,:) - RofBwrtCexpE(2,:))*1000, 'LineWidth', 1.5)
hold on
grid on
ylabel('RofBwrtCexpE_2 Error [m]')

subplot(3,2,5)
plot(t/3600, (x_ECEF(3,:) - RofBwrtCexpE(3,:))*1000, 'LineWidth', 1.5)
hold on
grid on
xlabel('Time [hr]')
ylabel('RofBwrtCexpE_3 Error [m]')

subplot(3,2,2)
plot(t/3600, (x_ECEF(4,:) - VofBwrtIexpE(1,:))*1000, 'LineWidth', 1.5)
hold on
grid on
ylabel('VofBwrtIexpE_1 Error [m/s]')

subplot(3,2,4)
plot(t/3600, (x_ECEF(5,:) - VofBwrtIexpE(2,:))*1000, 'LineWidth', 1.5)
hold on
grid on
ylabel('VofBwrtIexpE_2 Error [m/s]')

subplot(3,2,6)
plot(t/3600, (x_ECEF(6,:) - VofBwrtIexpE(3,:))*1000, 'LineWidth', 1.5)
hold on
grid on
xlabel('Time [hr]')
ylabel('VofBwrtIexpE_3 Error [m/s]')

% Sim vs. Matlab OE state comparison
figure(3)
sgtitle(sprintf('Sim vs. Matlab\nOrbital Element Errors'))
subplot(3,2,1)
plot(t/3600, (x_OE(1,:) - a)*1000, 'LineWidth', 1.5)
hold on
grid on
ylabel(sprintf('Semimajor Axis Error [m]'))

subplot(3,2,3)
plot(t/3600, x_OE(2,:) - ecc, 'LineWidth', 1.5)
hold on
grid on
ylabel(sprintf('Eccentricity Error [-]'))

subplot(3,2,5)
plot(t/3600, x_OE(3,:) - inc*(180/pi), 'LineWidth', 1.5)
hold on
grid on
xlabel('Time [hr]')
ylabel(sprintf('Inclination Error [deg]'))

subplot(3,2,2)
plot(t/3600, x_OE(4,:) - raan*(180/pi), 'LineWidth', 1.5)
hold on
grid on
ylabel(sprintf('RAAN Error [deg]'))

subplot(3,2,4)
plot(t/3600, x_OE(5,:) - aop*(180/pi), 'LineWidth', 1.5)
hold on
grid on
ylabel(sprintf('AOP Error [deg]'))

subplot(3,2,6)
plot(t/3600, x_OE(6,:) - ta*(180/pi), 'LineWidth', 1.5)
hold on
grid on
xlabel('Time [hr]')
ylabel(sprintf('True Anomaly Error [deg]'))

% Sim vs. Matlab other parameter comparisons
figure(4)
sgtitle(sprintf('Sim vs. Matlab\nOther Parameter Errors'))
subplot(3,2,1)
plot(t/3600, gmst_mat - gmst*(180/pi), 'LineWidth', 1.5)
hold on
grid on
ylabel('GMST Error [deg]')

subplot(3,2,2)
plot(t/3600, n_mat - n, 'LineWidth', 1.5)
hold on
grid on
ylabel(sprintf('Mean Motion Error [rad/s]'))

subplot(3,2,3)
plot(t/3600, (E_mat - E)*(180/pi), 'LineWidth', 1.5)
hold on
grid on
xlabel('Time [hr]')
ylabel(sprintf('Eccentric Anomaly Error [deg]'))

subplot(3,2,4)
plot(t/3600, (M_mat - M)*(180/pi), 'LineWidth', 1.5)
hold on
grid on
ylabel(sprintf('Mean Anomaly Error [deg]'))

subplot(3,2,5)
plot(t/3600, energy_mat - energy, 'LineWidth', 1.5)
hold on
grid on
ylabel(sprintf('Specific Energy Error [deg]'))

subplot(3,2,6)
plot(t/3600, fpa_mat - fpa*(180/pi), 'LineWidth', 1.5)
hold on
grid on
xlabel('Time [hr]')
ylabel(sprintf('Flight Path Angle Error [deg]'))


toc
