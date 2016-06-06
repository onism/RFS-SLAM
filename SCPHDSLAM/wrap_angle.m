function angle = wrap_angle(angle)


 rem = mod(angle,2*pi);
 if rem > pi
   rem = rem - 2 * pi;
 elseif rem < -pi
   rem = rem + 2 * pi;
 end

 angle = rem;
