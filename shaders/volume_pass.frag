    #version 330

uniform vec2 winDim;
uniform sampler2D frontTex;
uniform sampler2D backTex;
uniform sampler3D volumeTex;

out vec4 FragColor;

uniform float stepSize = 0.01;
uniform int maxIterations = 512;

void main()
{
    vec4 frontF = texelFetch (frontTex, ivec2 (gl_FragCoord.xy), 0);
    vec4 backF = texelFetch (backTex, ivec2 (gl_FragCoord.xy), 0);

    // Check if its outside of the cube volume
    if (frontF == backF)
        discard;

    vec3 direction = normalize(backF.xyz - frontF.xyz);

    vec3 pos = frontF.xyz;

    vec4 dst = vec4(0);
    vec3 step = direction * stepSize;
    for (int i = 0; i < maxIterations; i++) {
        vec4 src = vec4(texture(volumeTex, pos, 0).r);

//        dst.rgb = mix(dst.rgb, src.rgb, src.a);
//        dst.a = mix(dst.a, 1.0, src.a);

        // Max Intensity Projection (MIP)
        if (src.a > dst.a)
            dst = src;

        if(dst.a >= 0.99) {
           break;
        }

        pos += step;

        if (any(greaterThan(pos, vec3(1.0))))
           break;

        if (any(lessThan(pos, vec3(0.0))))
           break;
    }

//    FragColor = frontF - backF;
    FragColor = dst;
}
