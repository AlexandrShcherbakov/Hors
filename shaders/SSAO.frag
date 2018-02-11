#version 330

uniform sampler2D RandomPlanes;
uniform sampler2D PosTexture;
uniform int ScreenWidth;
uniform int ScreenHeight;

in vec4 vertNormal;

out vec4 outColor;

const int RANDOM_PLANES_TEXTURE_SIDE = 4;
const int SAMPLES_COUNT = 8;

void main() {
    const vec4 samples[SAMPLES_COUNT] = vec4[SAMPLES_COUNT](
        vec4(-0.5, -0.5, -0.5, 0),
        vec4(-0.5, -0.5,  0.5, 0),
        vec4(-0.5,  0.5, -0.5, 0),
        vec4(-0.5,  0.5,  0.5, 0),
        vec4( 0.5, -0.5, -0.5, 0),
        vec4( 0.5, -0.5,  0.5, 0),
        vec4( 0.5,  0.5, -0.5, 0),
        vec4( 0.5,  0.5,  0.5, 0)
    );

    const float radius = 20;
    vec2 screenSize = vec2(ScreenWidth, ScreenHeight);
    float visibleSamples = 0;
    ivec2 randomPlaneindex = ivec2(gl_FragCoord.xy) % RANDOM_PLANES_TEXTURE_SIDE;
    vec3 randomPlane = texture(RandomPlanes, vec2(randomPlaneindex) / RANDOM_PLANES_TEXTURE_SIDE).xyz;
    vec4 pos = texture(PosTexture, gl_FragCoord.xy / screenSize);
    vec4 normal = normalize(vertNormal);

    for (int i = 0; i < SAMPLES_COUNT; ++i) {
        vec3 reflectedSample = reflect(samples[i].xyz, randomPlane);
        vec2 sampleTextureCoord = (gl_FragCoord.xy + reflectedSample.xy * radius) / screenSize;
        vec4 samplePos = texture(PosTexture, sampleTextureCoord);
        visibleSamples += int(dot(normal, normalize(samplePos - pos)) < 1e-5);
    }
    outColor = vec4(visibleSamples / SAMPLES_COUNT);
}
