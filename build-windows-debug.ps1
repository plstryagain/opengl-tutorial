mkdir -Force ./build
cd ./build
cmake -DCMAKE_BUILD_TYPE=Debug -DGLM_ROOT="$Env:GLM_ROOT" -DGLFW_ROOT="$Env:GLFW_ROOT" -DGLEW_ROOT="$Env:GLEW_ROOT" -DCMAKE_MAKE_PROGRAM="C:\\Program Files\\Ninja\\ninja.exe" -G "Ninja" ..
cmake --build .