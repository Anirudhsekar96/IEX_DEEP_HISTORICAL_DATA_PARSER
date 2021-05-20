# IEX Depth of Book Historical Data (DEEP) Parser
<br>

<ol>

## <li> Introduction <br> </li>

This project implements high performance parsing of IEX's depth of book "DEEP" historical data using C++. <br>
<br>

## <li> Data Availability and Specifications <br> </li>

Market Data can be obtained from

> https://iextrading.com/trading/market-data/
<br>
Data follows IEX DEEP v1.6 specification

> https://iextrading.com/docs/IEX%20Transport%20Specification.pdf <br>
> https://iextrading.com/docs/IEX%20DEEP%20Specification.pdf

This code extracts and decodes historical data from IEX DEEP specification.
<br>
<br>

## <li> Components </li>
<ol>
<li> Extract packets from gzipped data using tshark </li> 
<li> Decodes packets using C++ </li>
</ol>
<br>

## <li> Extracting Packet Payloads using TShark </li>
<ol>

### <li> Installing TShark </li>
Check if TShark is already installed
```bash
tshark --version
```
Install TShark if required
```bash
sudo apt update
sudo apt-get install tshark
```
### <li> Extract Packets </li>
Run the following code to get raw payload of the pcap packets
```bash
tshark -r <gz_file> -T fields -e data > <extracted_file_name>
```
</ol>
<br>

## <li> Decoding Packets using C++ </li>
<ol>

### <li> Installing CMake </li>
Check if there is an existing installation of cmake
```bash
cmake --version
```

Install CMake if required
```
sudo apt update
sudo apt-get install cmake
```

### <li> Build and Test Parser using CMake </li>
```bash
mkdir build
cmake -S ./ -B build && cmake --build build
cd build && ctest
```
### <li> Decode Payloads </li>
Decode payloads into csv files
```bash
 ./iex_deep_parser <input_file> <output_file_dir>
```
</ol>

<br>

## <li> Leveraging Parallelism using GNU Parallel </li>
<ol>

### <li> Installing GNU Parralel</li>
Check if GNU Parallel is already installed
```bash
parallel --version
```
Install GNU Parallel if required
```bash
sudo apt update
sudo apt install parallel
```
### <li> Parallelizing Payload Extraction </li>
Run the following commands in terminal to extract payloads from gzipped pcap files parallely
```bash
# Define number of parallel jobs
export jobs=<Number_of_Parallel_Jobs>

# Define staggeration delay in seconds between jobs launches 
# We add delay to avoid IO overload
export delay=<Delay_in_Starting_Jobs> 

# Define input and output directory
# All paths are absolute
export input_dir=<gz_dir>
export output_dir=<output_dir>

# CD into input dir
cd $input_dir

# Parallel code to extract payload into output dir
ls *.gz | parallel "basename {} .pcap.gz" | parallel --retry-failed --shuf --jobs $jobs --delay $delay --eta --progress "tshark -r $input_dir{}.pcap.gz -T fields -e data > $output_dir{}"
```
### <li> Parallelizing Payload Decoding </li>
Run the following commands in terminal to decode the payloads and save them to csv parallely
```bash
# Define number of parallel jobs
export jobs=<Number_of_Parallel_Jobs>

# Define staggeration delay in seconds between jobs launches 
# We add delay to avoid IO overload
export delay=<Delay_in_Starting_Jobs> 

# Define input and output directory
# All paths are absolute
export input_dir=<payload_dir>
export output_dir=<output_dir>
export iex_deep_parser_path=<location_of_parser_base_folder>

# CD into input dir
cd $input_dir

# Parallel code to decode payloads
ls * | parallel --retry-failed --shuf --jobs $n_jobs --delay $delay --eta --progress '$iex_deep_parser_path/build/iex_deep_parser $input_dir{} $output_dir{}'

```

</ol>

</ol>
