# Image compression

For this school project, I implemented image compression using a quad-tree data structure. The core concept involved replacing areas of the image with low color variability. Pixels within a specified variance or average color threshold were pruned to compress the image. To ensure efficient memory management, I applied RAII principles and defined custom destructors.