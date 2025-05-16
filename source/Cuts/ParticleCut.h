#ifndef PARTICLECUT_H
#define PARTICLECUT_H

bool electronDVCScut(double px, double py, double pz, int pid);

bool protonDVCScut(double px, double py, double pz, int pid, double target_mass);

bool photonDVCScut(double px, double py, double pz, int pid);

#endif // PARTICLECUT_H