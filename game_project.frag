#version 400

in vec2 texture_coordinates;
in vec3 normal_eye, position_eye;

uniform sampler2D basic_texture;

out vec4 frag_colour;

uniform mat4 V, M;

vec3 light_position_world = vec3(9.0, 37.0, 8.0); // position of light source
vec3 Ls = vec3(1.0, 1.0, 1.0); // White
vec3 Ld = vec3(0.7, 0.7, 0.7); // Dull white
vec3 La = vec3(0.2, 0.2, 0.2); // Grey

vec3 Ks = vec3(1.0, 1.0, 1.0); // specular light colour
vec3 Kd = vec3(1.0, 0.5, 0.0); // diffuse light colour
vec3 Ka = vec3(1.0, 1.0, 1.0); // ambient light colour

float specular_exponent = 100.0;

void main () {

	vec3 Ia = La * Ka; // ambient Intensity

	vec3 light_position_eye = vec3(V * vec4(light_position_world, 1.0));
	vec3 distance_to_light_eye = light_position_eye - position_eye;
	vec3 direction_to_light_eye = normalize(distance_to_light_eye);

	float dot_prod = dot(direction_to_light_eye, normalize(normal_eye));
	dot_prod = max(dot_prod, 0.0);
	vec3 Id = Ld * Kd * dot_prod;

	vec3 surface_to_viewer_eye = normalize(-position_eye);

	// Blinn part
	vec3 half_way_eye = normalize(surface_to_viewer_eye + direction_to_light_eye);
	float dot_prod_specular = max (dot (half_way_eye, normalize(normal_eye)), 0.0);
	float specular_factor = pow (dot_prod_specular, specular_exponent);

	vec3 Is = Ls * Ks * specular_factor;

	//frag_colour = vec4(Is + Id + Ia, 1.0);

	vec4 texel = texture(basic_texture, texture_coordinates);
	frag_colour = texel * vec4(Is + Id + Ia, 1.0);
}