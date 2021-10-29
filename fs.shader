#version 400
in vec3
position_eye,
normal_eye;
uniform mat4 view_mat_shader;
in vec2 texture_coordinates;
uniform sampler2D basic_texture;
out vec4 frag_colour;
void main() {
	vec3 light_position_world = vec3(1.0, 20, 10);
	vec3 light_position_eye = vec3(view_mat_shader * vec4(light_position_world, 2.0));
	vec3 postion_viewer = vec3(0.0, 0.0, 0.0);
	vec3 n_eye = normalize(normal_eye);
	vec3 distance_to_light_eye = light_position_eye - position_eye;
	vec3 direction_to_light_eye = normalize(distance_to_light_eye);
	vec3 surface_to_viewer_eye = postion_viewer - position_eye;
	surface_to_viewer_eye = normalize(surface_to_viewer_eye);
	float dot_prod = dot(direction_to_light_eye, n_eye);
	dot_prod = max(dot_prod, 0.0);
	vec3 Ld = vec3(0.7, 0.7, 0.7);
	vec3 Kd = vec3(1.0, 0.5, 0.0);
	vec3 Id = Ld * Kd * dot_prod;
	vec3 half_way_eye = surface_to_viewer_eye + direction_to_light_eye;
	half_way_eye = normalize(half_way_eye);
	float dot_prod_specular = dot(half_way_eye, n_eye);
	dot_prod_specular = max(dot_prod_specular, 0.0);
	float specular_exponent = 100.0;
	float specular_factor = pow(dot_prod_specular, specular_exponent);
	vec3 Ls = vec3(1.0, 1.0, 1.0);
	vec3 Ks = vec3(1.0, 1.0, 1.0);
	vec3 Is = Ls * Ks * specular_factor;
	vec3 La = vec3(0.5, 0.5, 0.5);
	vec3 Ka = vec3(1.0, 1.0, 1.0);
	vec3 Ia = La * Ka;
	vec4 texel = texture (basic_texture, texture_coordinates);
	frag_colour = vec4(Is + Id + Ia, 1.0) *texel;
}