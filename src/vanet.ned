package contractbased;

network Vanet {
    parameters:
        int numVehicles = 20;
    submodules:
        baseStation: BaseStation;
        vehicles[numVehicles]: Vehicle;
    connections:
        for i=0..numVehicles-1 {
            baseStation.vehicles++ <--> vehicles[i].baseStation;
        }
        for i=0..numVehicles-1, for j=i+1..numVehicles-1 {
            vehicles[i].vehicles++ <--> vehicles[j].vehicles++;
        }
}