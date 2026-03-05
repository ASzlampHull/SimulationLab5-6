#version 450

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
    vec3 eyePos;
    float time;
    vec3 lightDir;
    vec3 lightColor;
} ubo;

layout(push_constant) uniform PushConstants {
    mat4 model;
    vec3 ambientMat;
    vec3 diffuseMat;
    vec3 specularMat;
    vec3 emissiveMat;
    float shininess;
    float reflectivity;
    float opacity;
    uint isVertexShaded;
    uint hasNoTexture;
    vec3 lightColor;
    vec3 darkColor;
} pushConstants;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec3 fragWorldPos;
layout(location = 2) in vec3 fragWorldNormal;
layout(location = 3) in vec2 fragTexCoord;
layout(location = 4) in vec3 fragLightPos_tangent;
layout(location = 5) in vec3 fragViewPos_tangent;
layout(location = 6) in vec3 fragPos_tangent;

layout(location = 0) out vec4 outColor;

layout(binding = 1) uniform sampler2D texSampler;

vec3 PerPixelShading()
{
    //Amient shading
    vec3 lightColor = ubo.lightColor;
    vec3 ambientMaterial = pushConstants.ambientMat;

    //Diffuse shading
    vec3 norm = normalize(fragWorldNormal);
    vec3 lightDir = normalize(ubo.lightDir - fragWorldPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    vec3 diffMaterial = pushConstants.diffuseMat;

    // Specular shading
    vec3 viewDir = normalize(ubo.eyePos - fragWorldPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float shininess = pushConstants.shininess;
    float spec = pow(max(dot(reflectDir, viewDir), 0.0), shininess);
    vec3 specularMaterial = pushConstants.specularMat;
    
    // Emissive material
    vec3 emissiveMaterial = pushConstants.emissiveMat;

    vec3 ambientLight = ambientMaterial * lightColor;
    vec3 diffuseLight = diffMaterial * lightColor * diffuse;
    vec3 specularLight = specularMaterial * lightColor * spec;
    vec3 emissiveLight = emissiveMaterial * lightColor;
    vec3 textureLight = texture(texSampler, fragTexCoord).rgb * fragColor;
    vec3 litColor = (ambientLight + diffuseLight + specularLight + emissiveLight) * textureLight;

    return litColor;
}

vec3 CheckerboardWorld(vec3 pos, float scale, vec3 color1, vec3 color2) {
    // Use the X and Z world coordinates for the checkerboard
    vec2 coord = pos.xz * scale;
    float checker = mod(floor(coord.x) + floor(coord.y), 2.0);
    return mix(color1, color2, checker);
}

void main() {        
    float opacity = pushConstants.opacity;
    
    if (pushConstants.hasNoTexture != 0) {
        // Procedural checkerboard: scale controls the number of squares
        float checkerScale = 2.0; // Adjust for size in world units
        vec3 colorA = pushConstants.lightColor; // Use light color for one of the checker colors
        vec3 colorB = pushConstants.darkColor; // Use dark color for the other checker color
        vec3 checkerColor = CheckerboardWorld(fragWorldPos, checkerScale, colorA, colorB);
        outColor = vec4(checkerColor, opacity);
        return;
    }
    if (pushConstants.isVertexShaded != 0) 
    {
        outColor = vec4(fragColor * texture(texSampler, fragTexCoord).rgb, opacity);
    }
    else
    {
        vec3 litColor = PerPixelShading();
        outColor = vec4(litColor, opacity);
    }
}