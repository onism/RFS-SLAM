function z = compute_measurement(pos,feature,meas)

dx = feature(1,:) - pos(1);
dy = feature(2,:) - pos(2);
r2 = dx^2 + dy^2;
bearing = wrap_angle(atan2(dy,dx) - pos(2));
r = sqrt(r2);
z = [];

for i = 1 : size(feature,2)
   if r(i)< meas.Range && bearing(i) < meas.FieldofView
     z = [z; r(i) bearing(i) ]
   end
end
