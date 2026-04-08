//
//  VertexShader.glsl
//  OpenGlProject2
//
//  Created by Мария Кутрань on 05.04.2026.
//
#version 330 core
layout (location = 0) in vec3 aPos;
void main(){
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
