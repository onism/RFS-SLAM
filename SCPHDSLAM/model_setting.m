% simulation
clear
nSteps = 100;

dt = 0.02; % time units between each step

maxLmapSize = 20; % maximum number of feature in local submaps

SensorSettings.FieldofView = pi; %  field of view
SensorSettings.Range = 10;
% measuremen noise
SensorSettings.Rng_noise = 0.25;
SensorSettings.Brg_noise = 0.0349; % 2 degree
SensorSettings.clutterRate = 20;
SensorSettings.pd = 0.95;
R = diag([SensorSettings.Rng_noise; SensorSettings.Brg_noise]).^2;

initial_state = [0,0,0,2,0,0.2]' ;

motiom_model.l = 2.83;
motiom_model.h = 0.76;
motiom_model.a = 3.78;
motiom_model.b = 1.21-1.42/2;
sigmaVel = 2;
sigmaSteer =     0.0873; %5 degrees
Q = diag([sigmaVel,sigmaSteer]).^2;
initial_state = initial_state(1:3) ;

% static map definition
mapArea = [[-20,-20];[20,20]];
mapRange = diff(mapArea);

 % random map
 nFeatures = 80;
 staticMap = [rand(1,nFeatures)*mapRange(1) + mapArea(1,1); rand(1,nFeatures)*mapRange(2) + mapArea(1,2)];
 dists = sum(staticMap.^2);
 [~,idx] = sort(dists,'ascend');
 staticMap = staticMap(:,idx);


 %[traj,control_true] = generateAckermanTrajectory(initial_state,motiom_model,staticMap,dt);
load('AckermanTrajectory.mat')
control_true = control;
 for k = 1:numel(control_true)
       control_noisy(k).u(1) = control_true(k).u(1) + sigmaVel*randn() ;
       control_noisy(k).u(2) = wrap_angle(control_true(k).u(2) + sigmaSteer*randn() ) ;
end

sim.control_true = control_true ;
sim.control_noisy = control_noisy ;


% generate measurement
measurements = cell(nSteps);
for i = 1 : nSteps
  z = compute_noisy_measurement(traj(:,i),staticMap,SensorSettings);
  measurements{i} = z;
end
