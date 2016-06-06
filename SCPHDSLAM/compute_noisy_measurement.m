function z  = compute_noisy_measurement(pos,feature,meas)

z_clean = compute_measurement(pos,feature,meas);
nz = size(z_clean,1);
detected = [];
n_detected = 0;
for i = 1 : nz
  if rand < meas.pd
    n_detected = n_detected + 1;
    detected(n_detected,:) = z_clean(i,:);
 end
end

 % add noise
 range_noise = randn(1,n_detected) * meas.Rng_noise;
 bearing_noise = randn(1,n_detected) * meas.Brg_noise;

 z_noisy = detected + [range_noise bearing_noise];

 z_noisy(1,:) = wrap_angle(z_noisy(1,:));

 % add clutter
 n_clutter = poissrnd(meas.clutterRate);

 z_clutter(1,:) = rand(1,n_clutter) * meas.Range;
 z_clutter(2,:) = rand(1,n_clutter) * meas.FieldofView;
 z = [z_noisy z_clutter];           
