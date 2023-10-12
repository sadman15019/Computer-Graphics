#version 330 core
out vec4 FragColor;


struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};



struct PointLight {
    vec3 position;
    vec3 direction;
    
    float k_c;  // attenuation factors
    float k_l;  // attenuation factors
    float k_q;  // attenuation factors
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    
    float k_c;  // attenuation factors
    float k_l;  // attenuation factors
    float k_q;  // attenuation factors

    float cos_theta; //total area in which there will be light 
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct DirectionalLight {
    vec3 direction;
    
    float k_c;  // attenuation factors
    float k_l;  // attenuation factors
    float k_q;  // attenuation factors
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


#define NR_POINT_LIGHTS 2
#define NR_SPOT_LIGHTS 4

in vec3 FragPos;
in vec3 Normal;

uniform bool directionallighton=true;
uniform bool spotlight1on=true;
uniform bool spotlight2on=true;
uniform bool spotlight3on=true;
uniform bool spotlight4on=true;
uniform bool pointlight1on=true;
uniform bool pointlight2on=true;

uniform vec3 viewPos;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform Material material;
uniform DirectionalLight directionallight;
uniform  SpotLight  spotlight[NR_SPOT_LIGHTS];

// function prototypes
vec3 CalcPointLight(Material material, PointLight light, vec3 N, vec3 fragPos, vec3 V);
vec3 CalcSpotLight(Material material, SpotLight light, vec3 N, vec3 fragPos, vec3 V);
vec3 CalcDirectionalLight(Material material, DirectionalLight light, vec3 N, vec3 V);
vec3 CalcDirectionalLightoff(Material material, DirectionalLight light, vec3 N, vec3 V);

void main()
{
    // properties
    vec3 N = normalize(Normal);
    vec3 V = normalize(viewPos - FragPos);
    
    vec3 result;
    // point lights
    if(directionallighton==true)
    {
          result +=CalcDirectionalLight(material, directionallight, N, V);
    }
    
    if(pointlight1on==true)result += CalcPointLight(material, pointLights[0], N, FragPos, V);
    if(pointlight2on==true)result += CalcPointLight(material, pointLights[1], N, FragPos, V);

  
     if(spotlight1on==true){result += CalcSpotLight(material, spotlight[0], N, FragPos, V);}
     if(spotlight2on==true){result += CalcSpotLight(material, spotlight[1], N, FragPos, V);}
     if(spotlight3on==true){result += CalcSpotLight(material, spotlight[2], N, FragPos, V);}
     if(spotlight4on==true){result += CalcSpotLight(material, spotlight[3], N, FragPos, V);}
    
        
    
   
    FragColor = vec4(result, 1.0);
}

// calculates the color when using a point light.
vec3 CalcPointLight(Material material, PointLight light, vec3 N, vec3 fragPos, vec3 V)
{
    vec3 L = normalize(light.position - fragPos);
    vec3 R = reflect(-L, N);
    
    vec3 K_A = material.ambient;
    vec3 K_D = material.diffuse;
    vec3 K_S = material.specular;
    
    // attenuation
    float d = length(light.position - fragPos);
    float attenuation = 1.0 / (light.k_c + light.k_l * d + light.k_q * (d * d));
    
    vec3 ambient = K_A * light.ambient;
    vec3 diffuse = K_D * max(dot(N, L), 0.0) * light.diffuse;
    vec3 specular = K_S * pow(max(dot(V, R), 0.0), material.shininess) * light.specular;
    
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    
    return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(Material material, SpotLight light, vec3 N, vec3 fragPos, vec3 V)
{
    vec3 L = normalize(light.position - fragPos);
    vec3 R = reflect(-L, N);
    
    vec3 K_A = material.ambient;
    vec3 K_D = material.diffuse;
    vec3 K_S = material.specular;
    
    // attenuation
    float d = length(light.position - fragPos);
    float attenuation = 1.0 / (light.k_c + light.k_l * d + light.k_q * (d * d));
    
    vec3 ambient = K_A * light.ambient;
    vec3 diffuse = K_D * max(dot(N, L), 0.0) * light.diffuse;
    vec3 specular = K_S * pow(max(dot(V, R), 0.0), material.shininess) * light.specular;


    float cos_alp = dot(L, normalize(-light.direction));
    float intensity;
    if(cos_alp<light.cos_theta)
    {
        intensity = 0.0;
    }
    else
    {
        intensity = cos_alp;
    }
    
    ambient *= attenuation*intensity;
    diffuse *= attenuation*intensity;
    specular *= attenuation*intensity;
    
    return (ambient + diffuse + specular);
}

vec3 CalcDirectionalLight(Material material, DirectionalLight light, vec3 N, vec3 V)
{
    vec3 L = normalize(-light.direction);
    vec3 R = reflect(-L, N);
    
    vec3 K_A = material.ambient;
    vec3 K_D = material.diffuse;
    vec3 K_S = material.specular;
    
    // no attenuation
 
    
    vec3 ambient = K_A * light.ambient;
    vec3 diffuse = K_D * max(dot(N, L), 0.0) * light.diffuse;
    vec3 specular = K_S * pow(max(dot(V, R), 0.0), material.shininess) * light.specular;

    
    return (ambient + diffuse + specular);
}

vec3 CalcDirectionalLightoff(Material material, DirectionalLight light, vec3 N, vec3 V)
{
    vec3 L = normalize(-light.direction);
    vec3 R = reflect(-L, N);
    
    vec3 K_A = material.ambient;
    vec3 K_D = material.diffuse;
    vec3 K_S = material.specular;
    
    // no attenuation
 
    
    vec3 ambient = K_A * light.ambient;
    vec3 diffuse = K_D * max(dot(N, L), 0.0) * light.diffuse;
    vec3 specular = K_S * pow(max(dot(V, R), 0.0), material.shininess) * light.specular;

    
    return (ambient*0.1 + diffuse*0.1 + specular*0.1);
}

