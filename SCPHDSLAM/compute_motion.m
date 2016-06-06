function [new_state] = compute_motion(motiom_model,prev_state,v_encoder,alpha,dt)
 % Acker motiom model transition
% author: junjie wang
% date: 2016/06/06
 x_prev = prev_state(1);
 y_prev = prev_state(2);
 theta_prev = prev_state(3);

 vc = v_encoder/(1 - tan(alpha)*motiom_model.h/motiom_model.l); % ref eq 37
 xc_dot = vc * cos(theta_prev);
 yc_dot = vc * sin(theta_prev);
 theta_dot = vc * tan(alpha)/motiom_model.l; % ref eq 36

 new_state(1) = x_prev + dt * (xc_dot + theta_dot * (motiom_model.a * sin(theta_prev) + motiom_model.b * cos(theta_prev)));
 new_state(2) = y_prev + dt * (yc_dot + theta_dot * (motiom_model.a * cos(theta_prev) - motiom_model.b * sin(theta_prev)));
 new_state(3) = wrap_angle(theta_prev + dt * theta_dot); % ref eq 35
