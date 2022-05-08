#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class MinHeap
{
    vector<pair<long long int, int>> heap;

public:
    void do_balance()
    {
        long long int idx_parent;
        long long int idx = heap.size() - 1;
        if ((idx % 2) != 0)
        {
            idx_parent = idx / 2;
        }
        else
        {
            idx_parent = (idx / 2) - 1;
        }
        while (idx_parent >= 0 && heap[idx].first < heap[idx_parent].first)
        {
            swap(heap[idx], heap[idx_parent]);
            idx = idx_parent;
            if ((idx % 2) != 0)
            {
                idx_parent = idx / 2;
            }
            else
            {
                idx_parent = (idx / 2) - 1;
            }
        }
    }

    void insert(pair<long long int, int> p)
    {
        heap.push_back(p);
        do_balance();
    }

    void heapify(long long int i,int a)
    {
        long long int l = (2 * i) + 1;
        long long int r = (2 * i) + 2;
        long long min_index = -1;
        if (l < heap.size() && heap[l].first < heap[i].first)
        {
            min_index = l;
        }
        else
        {
            min_index = i;
        }
        if (r < heap.size() && heap[r].first < heap[min_index].first)
        {
            min_index = r;
        }
        if (i != min_index)
        {
            swap(heap[i], heap[min_index]);
            heapify(min_index,1);
        }
    }

    pair<long long int, int> minimum()
    {
        int cId = heap[0].second;
        long long int minimum_ele = heap[0].first;
        long long int hpsz=heap.size();
        swap(heap[hpsz - 1],heap[0]) ;
        heap.pop_back();
        heapify(0,1);
        return {minimum_ele, cId};
    }
};

long long getFileSize(string input_file)
{
    long long c = 0;
    ifstream file(input_file);
    string con = "";
    while (getline(file, con, ','))
        c++;
    return c;
}
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "[-]Please provide all the arguments." << endl;
        return 0;
    }
    int chunks_num;
    string input_file = argv[1];
    string output_file = argv[2];
    int ChunkSize = 100000;
    long long int Filesize = getFileSize(input_file);
    vector<long long int> arr;
    chunks_num = Filesize / ChunkSize;
    if (Filesize % ChunkSize != 0)
    {
        chunks_num++;
    }
    ifstream file(input_file);
    string data = "";
    int tempfilenum = 1;
    int count = 0;
    while (getline(file, data, ','))
    {
        count++;
        long long int a = stoll(data, nullptr, 10);
        int n2;
        arr.push_back(a);
        if (count == ChunkSize)
        {
            
            string run_File = "temp" + to_string(tempfilenum);
            sort(arr.begin(), arr.end());
            FILE *currfile = fopen(run_File.c_str(), "w");
            long long int j = 0;
            while (j < arr.size())
            {

                fprintf(currfile, "%lld ", arr[j]);
                j++;
            }
            fclose(currfile);
            tempfilenum++;
            count = 0;
            arr.clear();
        }
    }
    if (arr.size() > 0)
    {
        string run_File = "temp" + to_string(tempfilenum);
        int n1;
        sort(arr.begin(), arr.end());
        FILE *currfile = fopen(run_File.c_str(), "w");
        for (long long i = 0; i < arr.size(); i++)
        {
            long long int num = arr[i];
            fprintf(currfile, "%lld ", num);
        }
        fclose(currfile);
        arr.clear();
        count = 0;
        tempfilenum++;
    }
    tempfilenum--;
    FILE *out_file = fopen(output_file.c_str(), "w");
    if (out_file == NULL)
    {
        cout << "error opening output file" << endl;
        return 0;
    }
    FILE *intermediate_files[tempfilenum];
    int i=0;
    while(i<tempfilenum)
    {
        string inter_file_name = "temp" + to_string(i + 1);
        intermediate_files[i] = fopen(inter_file_name.c_str(), "r");
        i++;
    }
    MinHeap h; 
    pair<long long int, int> harr;
    int filescount = 0;
    i=0;
    while(i<tempfilenum)
    {
        if (fscanf(intermediate_files[i], "%lld ", &harr.first) != EOF)
        {
            harr.second = i;
            
        }
        else
        {
            break;
        }
        h.insert(harr);
        i++;
    }
    int cnt = 1;
    while (filescount != tempfilenum)
    {
        auto item = h.minimum();
        int run_id = item.second;
        long long int number = item.first;
        if (cnt != Filesize)
        {
            fprintf(out_file, "%lld,", number);
            
        }
        else
        {
            fprintf(out_file, "%lld", number);
        }
        cnt++;
        pair<long long int, int> new_pair;
        if (fscanf(intermediate_files[run_id], "%lld ", &new_pair.first) == 1)
        {
            new_pair.second = run_id;
            h.insert(new_pair);
        }
        else
        {
            filescount++;
        }
    }
    i=0;
    while(i<tempfilenum)
    {
        fclose(intermediate_files[i]);
        string tem_file_name = "temp" + to_string(i + 1);
        remove(tem_file_name.c_str());
        i++;
    }
    fclose(out_file);
    return 0;
}