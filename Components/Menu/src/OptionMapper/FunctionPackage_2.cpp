#include "../../include/FunctionPackage_2.h"

void sumatoria(){

    fputs("FunPac_2\n",stdout);

    std::string arg_v = (*ArgumentsLoader::getInstance())['v'];
    if (arg_v == ""){
        fputs("moda: Debe ingresar un vector con -v para usar esta funcion, como -v \"1;2;5;2;3;5\"\n",stdout);
        return;
    }

    unsigned long long sum = 0;
    auto vec = splitInt(arg_v,';');
    if (vec.second){
        for (const auto& num : vec.first)
            sum += num;
        printf("sumatoria: El resultado de la suma del vector es: %llu\n",sum);
    }
    else
        printf("sumatoria: El vector ingresado -v {%s} es invalido, no puedes usar esta funcion\n",(*ArgumentsLoader::getInstance())['v'].c_str());
}

void promedio(){

    fputs("FunPac_2 ",stdout);

    std::string arg_v = (*ArgumentsLoader::getInstance())['v'];
    if (arg_v == ""){
        fputs("moda: Debe ingresar un vector con -v para usar esta funcion, como -v \"1;2;5;2;3;5\"\n",stdout);
        return;
    }
    unsigned long long sum = 0;
    auto vec = splitInt(arg_v,';');
    if (vec.second){
        for (const auto& num : vec.first)
            sum += num;
        printf("promedio: El promedio del vector es: %f\n",(float)sum/vec.first.size());
    }
    else
        printf("promedio: El vector ingresado -v {%s} es invalido, no puedes usar esta funcion\n",(*ArgumentsLoader::getInstance())['v'].c_str());

}

void moda(){

    fputs("FunPac_2 ",stdout);

    std::string arg_v = (*ArgumentsLoader::getInstance())['v'];
    if (arg_v == ""){
        fputs("moda: Debe ingresar un vector con -v para usar esta funcion, como -v \"1;2;5;2;3;5\"\n",stdout);
        return;
    }

    auto vec = splitInt(arg_v,';');
    if (vec.second){
        robin_hood::unordered_map<int, unsigned int> count;
        for (const auto& num : vec.first)
            count[num]++;
        std::pair<int, unsigned int> moda(-1,0);
        for (const auto& counted : count)
            if (counted.second > moda.second)
                moda.first = counted.first, moda.second = counted.second;
        printf("moda: La moda es {%i} y aparece %u veces\n", moda.first, moda.second);
    }
    else
        printf("moda: El vector ingresado -v {%s} es invalido, no puedes usar esta funcion\n",(*ArgumentsLoader::getInstance())['v'].c_str());

}

void cuentaElementos(){

    fputs("FunPac_2 ",stdout);

    std::string arg_v = (*ArgumentsLoader::getInstance())['v'];
    if (arg_v == ""){
        fputs("moda: Debe ingresar un vector con -v para usar esta funcion, como -v \"1;2;5;2;3;5\"\n",stdout);
        return;
    }
    auto vec = splitInt(arg_v,';');
    if (vec.second)
        printf("cuentaElementos: El vector tiene %lu elementos.\n", vec.first.size());
    else
        printf("cuentaElementos: El vector ingresado -v {%s} es invalido, no puedes usar esta funcion\n",(*ArgumentsLoader::getInstance())['v'].c_str());

}

void verArgumentos(){
    fputs("FunPac_2:\n",stdout);
    for (const auto& e : ArgumentsLoader::getInstance()->getAllArgs()){
        printf("%c => %s\n", e.first,e.second.c_str());
    }
}