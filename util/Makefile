
all:aks new_aks

aks:aks.cpp
	clang++ -Ofast aks.cpp -o aks

new_aks:new_aks.cpp
	clang++ -Ofast new_aks.cpp -o new_aks
	#clang++ -ggdb new_aks.cpp -o new_aks

aks_opt:aks_opt.cpp
	clang++ -Ofast aks_opt.cpp -o aks_opt
	#clang++ -ggdb new_aks.cpp -o new_aks

clean:
	rm aks new_aks
