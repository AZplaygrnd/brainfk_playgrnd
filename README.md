# Brainfuck Interpreter

Simple command-line tool for interpreting the **[Brainfuck programming language](https://en.wikipedia.org/wiki/Brainfuck)**.

## Usage
```sh
$ docker build --target run-application -t bf_image .
$ docker run --rm -it bf_image ./examples/0_hello_world_example.bf
```

## Run Tests
```sh
$ docker build --target run-tests -t bf_image_tests .
$ docker run --rm -it bf_image_tests
```

## References
- https://en.wikipedia.org/wiki/Brainfuck
- https://onestepcode.com/brainfuck-compiler-c