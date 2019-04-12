%% Constants
% Data rate 100Hz
% Data range +- 8g

g = 9.8;

%% Hard brakes

% first hard brake from 30km/h to 0km/h
% brakes applied from data point 650 to 850

figure(1);
plot(hardbrake1.t(650:850), hardbrake1.x(650:850))
hold on;
plot(hardbrake1.t(650:850), hardbrake1.y(650:850))
hold on;
plot(hardbrake1.t(650:850), hardbrake1.z(650:850))
ylabel('Acceleration (m/s^2)')
xlabel('Time (s)')
title('Acceleration data on x,y,z axes when hard braking from 30km/h to 0km/h')
legend('x-acceleration','y-acceleration','z-acceleration')
grid on

% second hard brake from 40km/h to 0km/h
% brakes applied from data point 206 to 286

figure(2);
plot(hardbrake2.t(206:286), hardbrake2.x(206:286))
hold on;
plot(hardbrake2.t(206:286), hardbrake2.y(206:286))
hold on;
plot(hardbrake2.t(206:286), hardbrake2.z(206:286))
ylabel('Acceleration (m/s^2)')
xlabel('Time (s)')
title('Acceleration data on x,y,z axes when hard braking from 40km/h to 0km/h')
legend('x-acceleration','y-acceleration','z-acceleration')
grid on

% fourth hard brake from 60km/h to 5km/h
% brakes applied from data point 160 to 252

figure(3);
plot(hardbrake4.t(160:252), hardbrake4.x(160:252))
hold on;
plot(hardbrake4.t(160:252), hardbrake4.y(160:252))
hold on;
plot(hardbrake4.t(160:252), hardbrake4.z(160:252))
ylabel('Acceleration (m/s^2)')
xlabel('Time (s)')
title('Acceleration data on x,y,z axes when hard braking from 60km/h to 5km/h')
legend('x-acceleration','y-acceleration','z-acceleration')
grid on

%% Speed bump test

figure(4);
plot(speedbump.t(370:470), speedbump.x(370:470))
hold on;
plot(speedbump.t(370:470), speedbump.y(370:470))
hold on;
plot(speedbump.t(370:470), speedbump.z(370:470))
ylabel('Acceleration (m/s^2)')
xlabel('Time (s)')
title('Acceleration data on x,y,z axes when passing over speedbumps')
legend('x-acceleration','y-acceleration','z-acceleration')
grid on

%% regular drives passing over some potholes

figure(5);
plot(drive4.t(23604:23828), drive4.x(23604:23828))
hold on;
plot(drive4.t(23604:23828), drive4.y(23604:23828))
hold on;
plot(drive4.t(23604:23828), drive4.z(23604:23828))
ylabel('Acceleration (m/s^2)')
xlabel('Time (s)')
title('Acceleration data on x,y,z axes when passing over a deep pothole at 40km/h')
legend('x-acceleration','y-acceleration','z-acceleration')
grid on