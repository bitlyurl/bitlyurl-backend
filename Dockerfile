FROM drogonframework/drogon:latest AS builder

ADD ./ /app

WORKDIR /app/build

RUN cmake .. && cmake --build . 

COPY /app/build/bitlyurl-backend /app

CMD [ "./bitlyurl-backend","/configs/backend.json"]

