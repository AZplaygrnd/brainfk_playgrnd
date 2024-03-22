FROM gcc:9.5.0-bullseye as run-application 
WORKDIR /application
COPY . /application

RUN gcc ./src/*.c src/lib/*.c -I./include -o ./bin/interpreter.bin -std=c99 -Wall -Wextra -pedantic

ENTRYPOINT ["./docker/docker.run.sh"]

FROM gcc:9.5.0-bullseye as run-tests
WORKDIR /application
COPY . /application

CMD ["sh", "./docker/docker.run-tests.sh"]