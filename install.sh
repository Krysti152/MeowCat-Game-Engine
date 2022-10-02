#!/bin/bash

echo "-----MeowCat Game Engine Installer-----"
echo "SFML libraries are needed to working properly."
sudo mkdir /usr/include/MCGE;
sudo cp engine.hpp /usr/include/MCGE;
sudo cp objects.hpp /usr/include/MCGE;
mkdir ~/MCGE_projects
echo "New projects created via MeowCat Game Engine Manager will be stored in ~/MCGE_projects."
echo "This is default directory for new projects created via MeowCat Game Engine Manager." > ~/MCGE_projects/readme.md
echo "-----MeowCat Game Engine was successfully installed-----"
