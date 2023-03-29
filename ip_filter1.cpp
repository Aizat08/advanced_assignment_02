#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

std::vector<std::string> split(const std::string&, char);
void print(std::vector<std::vector<int>>&);
void filter(std::vector<std::vector<int>>&);
void filter_and_print(std::vector<std::vector<int>>&, int, int);
void filter_any_print(std::vector<std::vector<int>>&, int);

int main(int argc, char const *argv[])
{
    try
    {   
        if(argc < 2){
            std::cerr << "Please pass data file as an argument!\n";
            return EXIT_FAILURE;
        }

        std::ifstream input{argv[1]};
        if(!input.is_open()){
            std::cerr << "Failed to open file! " << argv[1] << '\n';
            return EXIT_FAILURE;
        }
        
        std::vector<std::vector<int>> ip_pool;
        for(std::string line; std::getline(input, line);)
        {
            std::vector<int> ints;
            std::vector<std::string> v = split(line, '\t');
            std::vector<std::string> str = split(v.at(0), '.');
            std::transform(str.begin(), str.end(), std::back_inserter(ints),
                [&](std::string s){
                    return std::stoi(s); });

            ip_pool.push_back(ints);
            ints.clear();
        }

        //1. Sort in reverse lexicographic order and print
          std::cout << "All document in reverse lexicographic order: " << std::endl;
          filter(ip_pool);
          print(ip_pool);

        //2. Sort by the first byte and print
          std::cout << "Ip addressess by the first byte: " << std::endl;
          filter_and_print(ip_pool, 1, 0); // need to provide 0 !!!

        //3. Sort by first and second bytes and print
          std::cout << "Ip addressess by first and second bytes: " << std::endl;
          filter_and_print(ip_pool, 46, 70);

        //4. Sort by any byte and print
          std::cout << "Ip addressess by any byte: " << std::endl;
          filter_any_print(ip_pool, 46);

    }  
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

std::vector<std::string> split(const std::string& str, char d){
    std::vector<std::string> r;
    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos){
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));
    return r;
}

void print(std::vector<std::vector<int>>& ips){
     for(auto ip = ips.begin(); ip != ips.end(); ++ip){
        for(auto ip_in = ip->begin(); ip_in != ip->end(); ++ip_in){
            if(ip_in != ip->begin()){
                std::cout << "."; }
            std::cout << *ip_in; }
        std::cout << std::endl; }
}

void filter(std::vector<std::vector<int>>& ips){
    std::sort(ips.begin(), ips.end(), 
        [](const std::vector<int>& v1, const std::vector<int>& v2) -> bool 
         {return v1 > v2;});
}

void filter_and_print(std::vector<std::vector<int>>& ips, int first, int second){
    filter(ips); // must sort first

    int start = std::distance(ips.begin(), std::find_if(
                ips.begin(), ips.end(), 
                [&](const std::vector<int>& v1) -> bool{   
                if(second == 0){return v1[0] == first;}
                return v1[0] == first && v1[1] == second;}));

    int end = std::count_if(ips.begin(), ips.end(), 
              [&](const std::vector<int>& v1) -> bool{
              if(second ==0){return v1[0] == first;}
              return v1[0] == first && v1[1] == second;});

    std::vector<std::vector<int>> vect;
    for(int i=start; i<start+end; ++i){
        vect.push_back(ips[i]);}

    print(vect);
    vect.clear();
}

void filter_any_print(std::vector<std::vector<int>>& ips, int value){

    filter(ips); //must sort first
    std::vector<std::vector<int>> vect;
    for(auto it = ips.begin(); it != ips.end(); ++it){
        if((std::find(it->begin(), it->end(), value)) != it->end()){ 
            vect.push_back(*it); }
    }

    print(vect);
    vect.clear();
}



