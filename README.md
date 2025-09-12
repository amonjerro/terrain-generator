# Terrain Generation Experiments

This repo is a collection of experiments for the creation of 2D terrain using a variety of techniques. All rendering of these terrains is done through the use of the SFML library.

## Noise based approach

The first approach being developed is the use of Perlin noise to create organic looking terrain and then using color coding to clarify the type of terrain created. Noise is being generated through a shader to reduce waiting time and iterate faster.

Below is an image of the type of noise currently being created by the tool.

<img width="1073" height="751" alt="image" src="https://github.com/user-attachments/assets/0bda68ee-b2a1-40a7-9e1c-7b84884fe5b8" />

With color coding, it generates this type of terrain.

<img width="1086" height="721" alt="image" src="https://github.com/user-attachments/assets/f87067ea-2bfd-48a3-9501-d88b6fd5df38" />


## Simulating weather patterns

The above noise maps can be taken as a height map. Additional layers detailing wind and humidity can be created and combined with each other to create more realistic representations of precipitation and thus simulate the creation or abscense of water sources, rivers and vegetation. Below is the output of a shader showing the interaction between the above noise map plus a wind and humidity layer.
