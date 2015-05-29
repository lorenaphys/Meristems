aux=H;

% HH(2:Nx+1,2:Ny+1)=H(1:Nx,1:Ny);
% HH(1,2:Ny+1)=H(2,1:Ny);
% HH(2:Nx+1,1)=H(1:Nx,2);
% HH(Nx+2,2:Ny+1)=H(Nx-1,1:Ny);
% HH(2:Nx+1,Ny+2)=H(1:Nx,Ny-1);
% HH(1,1)=H(2,2);
% HH(1,Ny+2)=H(2,Ny-1);
% HH(Nx+2,1)=H(Nx-1,2);
% HH(Nx+2,Ny+2)=H(Nx-1,Ny-1);
% lapH(1:Nx,1:Ny)=HH(2:Nx+1,3:Ny+2)+HH(2:Nx+1,1:Ny)+HH(3:Nx+2,2:Ny+1)+HH(1:Nx,2:Ny+1)-4*HH(2:Nx+1,2:Ny+1);    

lap=0*aux;
LapUx=lap;
LapUy=lap;
LapUz=lap;
% aux(:,2,:)=aux(:,1,:);
% aux(:,Ny,:)=aux(:,Ny-1,:);
% aux(2,:,:)=aux(1,:,:);
% aux(Nx,:,:)=aux(Nx-1,:,:);
% aux(:,:,2)=aux(:,:,1);
% aux(:,:,Nz)=aux(:,:,Nz-1);

for n=2:Ny-1
      LapUy(:,n,:)=aux(:,n-1,:)-2*aux(:,n,:)+aux(:,n+1,:); 
end
 for m=2:Nx-1;
      LapUx(m,:,:)=aux(m-1,:,:)-2*aux(m,:,:)+aux(m+1,:,:);
 end
for mm=2:Nz-1;
      LapUz(:,:,mm)=aux(:,:,mm-1)-2*aux(:,:,mm)+aux(:,:,mm+1);
end
     LapUy(:,1,:)=aux(:,2,:)-aux(:,1,:);
     LapUy(:,Ny,:)=aux(:,Ny-1,:)-aux(:,Ny,:);
     LapUx(1,:,:)=aux(2,:,:)-aux(1,:,:);
     LapUx(Nx,:,:)=aux(Nx-1,:,:)-aux(Nx,:,:);
     LapUz(:,:,1)=aux(:,:,2)-aux(:,:,1);
     LapUz(:,:,Nz)=aux(:,:,Nz-1)-aux(:,:,Nz);
     
     lapH=LapUx+LapUy+LapUz;
     
    lapH(1,1,1)=H(2,1,1)-H(1,1,1)+H(1,2,1)-H(1,1,1)+H(1,1,2)-H(1,1,1);
    lapH(1,Ny,1)=H(2,Ny,1)-H(1,Ny,1)+H(1,Ny,2)-H(1,Ny,1)+H(1,Ny-1,1)-H(1,Ny,1);
    lapH(Nx,1,1)=H(Nx,2,1)-H(Nx,1,1)+H(Nx,1,2)-H(Nx,1,1)+H(Nx-1,1,1)-H(Nx,1,1);
    lapH(1,1,Nz)=H(2,1,Nz)-H(1,1,Nz)+H(1,2,Nz)-H(1,1,Nz)+H(1,1,Nz-1)-H(1,1,Nz);
    
    lapH(Nx,Ny,1)=H(Nx-1,Ny,1)-H(Nx,Ny,1)+H(Nx,Ny-1,1)-H(Nx,Ny,1)+H(Nx,Ny,2)-H(Nx,Ny,1);
    lapH(Nx,1,Nz)=H(Nx-1,Ny,Nz)-H(Nx,1,Nz)+H(Nx,2,Nz)-H(Nx,1,Nz)+H(Nx,1,Nz-1)-H(Nx,1,Nz);    
    lapH(1,Ny,Nz)=H(2,Ny,Nz)-H(1,Ny,Nz)+H(1,Ny-1,Nz)-H(1,Ny,Nz)+H(1,Ny,Nz-1)-H(1,Ny,Nz); 
    lapH(Nx,Ny,Nz)=H(Nx-1,Ny,Nz)-H(Nx,Ny,Nz)+H(Nx,Ny-1,Nz)-H(Nx,Ny,Nz)+H(Nx,Ny,Nz-1)-H(Nx,Ny,Nz);          