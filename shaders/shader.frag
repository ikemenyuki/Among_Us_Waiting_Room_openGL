#version 330 core
// This is a sample fragment shader.

in float sampleExtraOutput;
in vec3 Normal;
in vec3 FragPos;
in vec3 viewPos;
in float type;
in float isPhong;
in float isLight;

uniform vec3 color;
//uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 direction;

// You can output many things. The first vec4 type output determines the color of the fragment
out vec4 fragColor;

void main()
{
    float ambientStrength = 0.25;
    vec3 ambient = ambientStrength * lightColor;
//    float dist = length(lightPos - FragPos);
//    float linear = 0.09;
//    float attenuation = 1.0 / (linear * dist);
//    ambient *= attenuation;
    // Use the color passed in. An alpha of 1.0f means it is not transparent.
    if (isLight == 1.0f) {
        fragColor = vec4(lightColor, sampleExtraOutput);
    }
    else{
        if (isPhong == 1.0f){
            vec3 lightDir = normalize(-direction);
//            float  dist = length(lightPos - FragPos);
            float diff = max(dot(Normal, lightDir), 0.0);
            float intensity= diff;
            vec3 diffuse = diff * lightColor;
            
            float specularStrength = 1;
            vec3 viewDir = normalize(viewPos - FragPos);
            vec3 reflectDir = reflect(-lightDir, Normal);
            // vec3 reflectDir = reflect(lightDir, Normal);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
            vec3 specular = specularStrength * spec * lightColor;
            vec3 result;
            float shinnyFactor = 3;
            if (type == 0.0f){
                ambient *= shinnyFactor;
                // ambient *= shinnyFactor;
                result = (ambient + specular * shinnyFactor * 3) * color;
            }
            else if (type == 1.0f){
                result = (ambient + diffuse * shinnyFactor) * color;
                //result = diffuse * color;
            }
            else if (type == 2.0f) {
                result = shinnyFactor * (ambient + diffuse + specular) * color;
            }
            else if (type == 3.0f) {
                result = lightColor;
                result = ambient;
            }
            fragColor = vec4(result, sampleExtraOutput);
            if (intensity > 0.95)
                fragColor = vec4(1.0,1,1,1.0) * fragColor;
            else if (intensity > 0.5)
                fragColor = vec4(0.7,0.7,0.7,1.0) * fragColor;
            else if (intensity > 0.05)
                fragColor = vec4(0.35,0.35,0.35,1.0) * fragColor;
            else
                fragColor = vec4(0.1,0.1,0.1,1.0) * fragColor;
//            vec3 V = normalize(viewPos - FragPos);
//            float edge = max(0.0f, dot(Normal, V));
//            if (edge < 0.01) {
//                fragColor  = vec4(1, 1, 1, 1);
//            }
        }
        else{
            if (type == 3.0f) fragColor = vec4(ambient, sampleExtraOutput);
            
            else{
                vec3 normColor = (vec3(1, 1, 1) + Normal) / 2;
                fragColor = vec4(normColor, sampleExtraOutput);
            }
        }
    }
    vec3 V = normalize(viewPos - FragPos);
    float edge = max(dot(normalize(Normal), V), 0.0f);
    if (edge < 0.3) {
        fragColor  = vec4(0, 0, 0, 1.0f);
    }
}
