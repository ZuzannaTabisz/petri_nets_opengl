

#version 330

uniform sampler2D tex;


uniform float lightIntensity;
uniform float kdFactor;
uniform float ksFactor;
uniform sampler2D shadowMap;




in vec2 i_tc;
in vec4 ic;
in vec4 i_lightColor1;
in vec4 i_lightColor2;
in vec4 l1;
in vec4 l2;
in vec4 n;
in vec4 v;
in vec4 FragPosLightSpace;

out vec4 pixelColor;

float ShadowCalculation(vec4 fragPosLightSpace) {

    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;  // [0,1] zakres jako pozycja tekstury


    float closestDepth = texture(shadowMap, projCoords.xy).r; 

    float currentDepth = projCoords.z;


    float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;

    return shadow;
}


void main(void) {
    vec4 ml1 = normalize(l1);
    vec4 ml2 = normalize(l2);
    vec4 mn = normalize(n);
    vec4 mv = normalize(v);
    vec4 mr1 = reflect(-ml1, mn);
    vec4 mr2 = reflect(-ml2, mn);

    vec4 kd = texture(tex, i_tc) * kdFactor;
    vec4 ks = texture(tex, i_tc) * ksFactor;
    vec4 ks_c = ic* ksFactor;

    float nl1 = max(dot(mn, ml1), 0.2) * lightIntensity;
    float nl2 = max(dot(mn, ml2), 0.2) * lightIntensity;
    float rv1 = pow(max(dot(mr1, mv), 0.2), 50) * lightIntensity;
    float rv2 = pow(max(dot(mr2, mv), 0.2), 50) * lightIntensity;

    vec4 diffuse = nl1 * i_lightColor1 * kd + nl2 * i_lightColor2 * kd;
    vec4 specular = rv1 * i_lightColor1 * ks + rv2 * i_lightColor2 * ks;

    vec4 diffuse_c = nl1 * i_lightColor1 * ic+ nl2 * i_lightColor2 * ic;
    vec4 specular_c = rv1 * i_lightColor1 * ks_c + rv2 * i_lightColor2 * ks_c;

    vec4 baseColor;
    vec4 lightContribution = diffuse + specular;

    float shadow = ShadowCalculation(FragPosLightSpace);

    
    float shadowIntensity = 0.5;


    if (kd.rgb == vec3(1.0, 1.0, 1.0)) {
        //normalne bia³e swiat³o
        //pixelColor = vec4(nl1 * ic.rgb + nl2 * ic.rgb, ic.a) + vec4(rv1 * ic.rgb + rv2 * ic.rgb, 0);


        baseColor = vec4(nl1 * ic.rgb + nl2 * ic.rgb, ic.a) * (1.0 - shadowIntensity * shadow) + vec4(rv1 * ic.rgb + rv2 * ic.rgb, 0);

        pixelColor = mix(baseColor,lightContribution, 0.5);
        

     }else {

        //normale bia³e swiat³o
        //pixelColor = vec4(nl1 * kd.rgb + nl2 * kd.rgb, kd.a) + vec4(rv1 * ks.rgb + rv2 *ks.rgb, 0);

        baseColor = vec4(nl1 * kd.rgb + nl2 * kd.rgb, kd.a) * (1.0 - shadowIntensity * shadow) + vec4(rv1 * ks.rgb + rv2 *ks.rgb, 0);

        pixelColor = mix(baseColor, lightContribution, 0.3);

    }
}