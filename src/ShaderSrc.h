#pragma once
//Source shader files.

//Doing it like this prevents the user from editing the files on the disk.
//I wrote a loader to load this data from a file, but it was really annoying to have to pass around GLSL files just to run the program.
//This is much simpler, and prevents malicous stuff with shader modification.

const char* fragSrc =
"#version 330 core\n"
"out vec4 FragColor;"
""
"in vec2 texCoord;"
"uniform sampler2D tex;"
"uniform float time;"
""
"void main()"
"{"
"	FragColor = texture(tex, texCoord);"
"}";

const char* vertSrc =
"#version 330 core\n"
"layout(location = 0) in vec3 aPos;"
"layout(location = 1) in vec2 aTexCoord;"
""
"out vec2 texCoord;"
""
"uniform mat4 model;"
"uniform mat4 view;"
"uniform mat4 projection;"
""
"void main()"
"{"
"	texCoord = aTexCoord;"
"	gl_Position = projection * view * model * vec4(aPos, 1.0);"
"}";