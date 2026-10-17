clear;

%% import sim input
simFile = fileread("inputs/sim.json");
simData = jsondecode(simFile);

spacecraftFile = fileread("inputs/spacecraft.json");
spacecraftData = jsondecode(spacecraftFile);

startTime   = simData.simStartTime;
endTime     = simData.simEndTime;
dt          = simData.timeStepRK4;

RwrtOexpN_0 = spacecraftData.initialState.RwrtOexpN;
VwrtOexpN_0 = spacecraftData.initialState.VwrtOexpN;

%% import sim output
T_RK4 = readtable("outputs/Spacecraft.csv");
time_RK4 = T_RK4.Time;
RwrtOexpN_RK4 = [T_RK4.RwrtOexpN_1, T_RK4.RwrtOexpN_2, T_RK4.RwrtOexpN_3]';
VwrtOexpN_RK4 = [T_RK4.VwrtOexpN_1, T_RK4.VwrtOexpN_2, T_RK4.VwrtOexpN_3]';

%% compare against ode45
x0_ECI = [RwrtOexpN_0; VwrtOexpN_0];
tspan = startTime:dt:endTime;
[t, x_ECI] = ode45(@(t, state) propagator(t, state), tspan, x0_ECI, Const.odeOpts);
x_ECI = x_ECI';

%% verify time vectors are equivalent
float_tol = 1e-12;
if any(abs(time_RK4 - t) > float_tol) || any(abs(time_FE - t) > float_tol)
    disp("Simulation and ode45 time vectors are not equivalent.");
end

%% plot results
% RK4 vs. ode45 comparison
figure(1)
sgtitle('RK4 vs. ODE45')
subplot(3,2,1)
plot(t, (x_ECI(1,:) - RwrtOexpN_RK4(1,:))*1000, 'LineWidth', 1.5)
hold on
grid on
xlabel('Time [s]')
ylabel('RwrtOexpN_1 Error [m]')

subplot(3,2,3)
plot(t, (x_ECI(2,:) - RwrtOexpN_RK4(2,:))*1000, 'LineWidth', 1.5)
hold on
grid on
xlabel('Time [s]')
ylabel('RwrtOexpN_2 Error [m]')

subplot(3,2,5)
plot(t, (x_ECI(3,:) - RwrtOexpN_RK4(3,:))*1000, 'LineWidth', 1.5)
hold on
grid on
xlabel('Time [s]')
ylabel('RwrtOexpN_3 Error [m]')

subplot(3,2,2)
plot(t, (x_ECI(4,:) - VwrtOexpN_RK4(1,:))*1000, 'LineWidth', 1.5)
hold on
grid on
xlabel('Time [s]')
ylabel('VwrtOexpN_1 Error [m/s]')

subplot(3,2,4)
plot(t, (x_ECI(5,:) - VwrtOexpN_RK4(2,:))*1000, 'LineWidth', 1.5)
hold on
grid on
xlabel('Time [s]')
ylabel('VwrtOexpN_2 Error [m/s]')

subplot(3,2,6)
plot(t, (x_ECI(6,:) - VwrtOexpN_RK4(3,:))*1000, 'LineWidth', 1.5)
hold on
grid on
xlabel('Time [s]')
ylabel('VwrtOexpN_3 Error [m/s]')

% position over time
figure(2)
sgtitle('Position Over Time')
plot3(x_ECI(1,:), x_ECI(2,:), x_ECI(3,:))
hold on
plot3(RwrtOexpN_RK4(1,:), RwrtOexpN_RK4(2,:), RwrtOexpN_RK4(3,:))
grid on
xlabel('x [km]')
ylabel('y [km]')
zlabel('z [km]')
legend('ode45', 'sim')

