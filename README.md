# andesrobot-ihr

Para construir el repositorio entrar a la carpeta receptionist y ejecutar

setup.sh

Se requiere la versión de OpenCV 4.8.0

Clonar el siguiente repositorio en receptionist/src

git clone https://github.com/BehaviorTree/BehaviorTree.ROS2.git

cd BehaviorTree.ROS2

colcon build

cd nlp_interfaces

colcon build

cd vision_interfaces

colcon build

Luego en la carpeta general

colcon build

Luego verificar que esté configurada la cámara, 

Luego configurar la entrada de audio y la salida de audio, verificar ID de dispositivos con (ejemplo de configuración en setup_audio.sh):

pacmd list sinks

pacmd list sources

Luego hay que levantar los servicios (cada uno en un terminal),

./findperson_run.sh

./ask_run.sh

./talk_run.sh

Luego ejecutar el árbol de comportamiento

./awake.sh

Y contestar las preguntas...
