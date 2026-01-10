FROM ubuntu:22.04

# Install dependencies
RUN apt-get update && apt-get install -y \
    g++ \
    libmysqlcppconn-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copy source files
COPY src/*.cpp src/*.h ./

# Copy config file
COPY src/DatabaseConfig.txt .

# Compile the application
RUN g++ -std=c++17 -o hotel_app *.cpp -lmysqlcppconn -lpthread

# Run the application
CMD ["./hotel_app"]
