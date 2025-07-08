#version 410 core

in vec3 v_vertexColors;

out vec4 fragColor;

void main()
{

// fragColor = vec4(1.0f, 0.5f, 0.0f,1.0f);

    fragColor = vec4(v_vertexColors.r, v_vertexColors.g,v_vertexColors.b,1.0f);

}
