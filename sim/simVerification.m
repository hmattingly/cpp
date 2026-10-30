clear; close all; tic

%% import sim input
simFile = fileread("inputs/sim.json");
simData = jsondecode(simFile);

spacecraftFile = fileread("inputs/spacecraft.json");
spacecraftData = jsondecode(spacecraftFile);

startTime   = 0.0;
endTime     = simData.simRunTime;
dt          = simData.timeStepRK4;

year = simData.epoch.year;
month = simData.epoch.month;
day = simData.epoch.day;
utc = simData.epoch.utc;

RwrtOexpN_0 = spacecraftData.initialState.RwrtOexpN;
VwrtOexpN_0 = spacecraftData.initialState.VwrtOexpN;

opts = Const.propOpts();
opts.J2 = spacecraftData.dynamics.J2;
opts.J3 = spacecraftData.dynamics.J3;
opts.J4 = spacecraftData.dynamics.J4;
opts.epoch = [year, month, day, utc];

%% import sim output
T = readtable("outputs/Spacecraft.csv");
time = T.Time;
RwrtOexpN = [T.RwrtOexpN_1, T.RwrtOexpN_2, T.RwrtOexpN_3]';
VwrtOexpN= [T.VwrtOexpN_1, T.VwrtOexpN_2, T.VwrtOexpN_3]';

%% compare against ode45
x0_ECI = [RwrtOexpN_0; VwrtOexpN_0];
tspan = startTime:dt:endTime;
[t, x_ECI] = ode45(@(t, state) propagator(t, state, opts), tspan, x0_ECI, Const.odeOpts);
x_ECI = x_ECI';

%% verify time vectors are equivalent
float_tol = 1e-12;
if any(abs(time - t) > float_tol)
    disp("Simulation and ode45 time vectors are not equivalent.");
end

%% plot results
% RK4 vs. ode45 comparison
figure(1)
sgtitle('RK4 vs. ODE45')
subplot(3,2,1)
plot(t, (x_ECI(1,:) - RwrtOexpN(1,:))*1000, 'LineWidth', 1.5)
hold on
grid on
xlabel('Time [s]')
ylabel('RwrtOexpN_1 Error [m]')

subplot(3,2,3)
plot(t, (x_ECI(2,:) - RwrtOexpN(2,:))*1000, 'LineWidth', 1.5)
hold on
grid on
xlabel('Time [s]')
ylabel('RwrtOexpN_2 Error [m]')

subplot(3,2,5)
plot(t, (x_ECI(3,:) - RwrtOexpN(3,:))*1000, 'LineWidth', 1.5)
hold on
grid on
xlabel('Time [s]')
ylabel('RwrtOexpN_3 Error [m]')

subplot(3,2,2)
plot(t, (x_ECI(4,:) - VwrtOexpN(1,:))*1000, 'LineWidth', 1.5)
hold on
grid on
xlabel('Time [s]')
ylabel('VwrtOexpN_1 Error [m/s]')

subplot(3,2,4)
plot(t, (x_ECI(5,:) - VwrtOexpN(2,:))*1000, 'LineWidth', 1.5)
hold on
grid on
xlabel('Time [s]')
ylabel('VwrtOexpN_2 Error [m/s]')

subplot(3,2,6)
plot(t, (x_ECI(6,:) - VwrtOexpN(3,:))*1000, 'LineWidth', 1.5)
hold on
grid on
xlabel('Time [s]')
ylabel('VwrtOexpN_3 Error [m/s]')

% position over time
figure(2)
sgtitle('Position Over Time')
plot3(x_ECI(1,:), x_ECI(2,:), x_ECI(3,:))
hold on
plot3(RwrtOexpN(1,:), RwrtOexpN(2,:), RwrtOexpN(3,:))
grid on
xlabel('x [km]')
ylabel('y [km]')
zlabel('z [km]')
legend('ode45', 'sim')

toc