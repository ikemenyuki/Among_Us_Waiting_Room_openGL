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
uniform vec3 lightColor;
uniform vec3 direction;

// You can output many things. The first vec4 type output determines the color of the fragment
out vec4 fragColor;

void main()
{
    float ambientStrength = 0.25;
    vec3 ambient = ambientStrength * lightColor;
    // Use the color passed in. An alpha of 1.0f means it is not transparent.
    if (isLight == 1.0f) {
        fragColor = vec4(lightColor, sampleExtraOutput);
    }
    else{
        if (isPhong == 1.0f){
            vec3 lightDir = normalize(-direction);
            float diff = max(dot(Normal, lightDir), 0.0);
            vec3 diffuse = diff * lightColor;
            
            float specularStrength = 0.5f;
            vec3 viewDir = normalize(viewPos - FragPos);
            vec3 reflectDir = reflect(-lightDir, Normal);
            // vec3 reflectDir = reflect(lightDir, Normal);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
            vec3 specular = specularStrength * spec * lightColor;
            vec3 result;
            float shinnyFactor = 1;
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
                result = (ambient + diffuse + specular) * color;
            }
            else if (type == 3.0f) {
                result = lightColor;
                result = ambient;
            }
            fragColor = vec4(result, sampleExtraOutput);
        }
        else{
            if (type == 3.0f) fragColor = vec4(ambient, sampleExtraOutput);
            
            else{
                vec3 normColor = (vec3(1, 1, 1) + Normal) / 2;
                fragColor = vec4(normColor, sampleExtraOutput);
            }
        }
    }
    
}

