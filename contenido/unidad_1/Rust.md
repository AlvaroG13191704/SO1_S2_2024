# 4. Rust

## 1.4.1. Conceptos básicos de Rust

### Introducción a Rust

- **Historia y evolución**
  - Rust fue desarrollado por Mozilla Research, con el primer lanzamiento estable en 2015.
  - Se diseñó para abordar problemas de memoria y concurrencia que son comunes en lenguajes como C y C++.
- **Propósito y filosofía del lenguaje**
  - Rust se centra en la seguridad, velocidad y concurrencia.
  - Busca ofrecer un sistema de tipos que prevenga errores de memoria y condiciones de carrera sin necesidad de un recolector de basura.

### Sintaxis básica

- **Variables y constantes**
  - Las variables en Rust son inmutables por defecto y se declaran con `let`.
  - Se puede hacer una variable mutable con `mut`.
  - Las constantes se declaran con `const` y deben tener un tipo explícito.

```rust
let x = 5;
let mut y = 10;
const MAX_POINTS: u32 = 100_000;
```

- **Tipos de datos primitivos**
 - Enteros: i8, i16, i32, i64, u8, u16, u32, u64
 - Punto flotante: f32, f64
 - Booleano: bool
 - Caracteres: char
   
- **Operadores y expresiones**
 - Aritméticos: +, -, *, /, %
 - Comparación: ==, !=, >, <, >=, <=
 - Lógicos: &&, ||, !

### Control de flujo
- **Condicionales**
 - Uso de if, else if, y else

```rust
let number = 6;
if number % 4 == 0 {
    println!("number is divisible by 4");
} else if number % 3 == 0 {
    println!("number is divisible by 3");
} else {
    println!("number is not divisible by 4, 3, or 2");
}
```

- **Bucles**
 - loop: Ejecuta un bloque de código repetidamente hasta que se interrumpa con break.
 - while: Ejecuta un bloque de código mientras una condición sea verdadera.
 - for: Itera sobre una colección de elementos.

```rust
let mut count = 0;
loop {
    count += 1;
    if count == 3 {
        break;
    }
}

while count != 0 {
    count -= 1;
}

for number in 1..4 {
    println!("{}", number);
}
```

### Funciones
- **Definición y llamada a funciones**

```rust
fn main() {
    let result = add(5, 3);
    println!("Result: {}", result);
}

fn add(x: i32, y: i32) -> i32 {
    x + y
}
```

- **Parámetros y retorno de valores**
 - Las funciones pueden recibir parámetros y devolver valores.
 - El tipo de retorno se especifica con ->.

- **Módulos y paquetes**
 - Organización del código en módulos
 - Los módulos permiten organizar el código en archivos y carpetas.
 - Se declaran con mod.

```rust
mod my_module {
    pub fn say_hello() {
        println!("Hello!");
    }
}

fn main() {
    my_module::say_hello();
}
```

- **Uso de Cargo para gestión de paquetes**
 - Cargo es la herramienta de gestión de paquetes y construcción de Rust.
 - Cargo.toml es el archivo de configuración donde se especifican las dependencias.

```rust
[dependencies]
rand = "0.8"
```

## 1.4.2. Conceptos únicos de Rust
### Propiedad y préstamos
- **Sistema de propiedad y cómo funciona**
 - Cada valor en Rust tiene una única propiedad.
 - Cuando el propietario sale de su alcance, el valor se libera.

```rust
let s1 = String::from("hello");
let s2 = s1; // s1 ya no es válido

println!("{}", s2); // Esto funciona
```

- **Préstamos (borrowing) y referencias (references)**
 - Se pueden tomar referencias a los valores sin tomar la propiedad.
 - Las referencias se crean con &.

```rust
let s1 = String::from("hello");
let len = calculate_length(&s1);

fn calculate_length(s: &String) -> usize {
    s.len()
}
```

- **Reglas de préstamo y mutabilidad**
 - Solo puede haber una referencia mutable a un valor en un momento dado.
 - Se pueden tener múltiples referencias inmutables.

```rust
let mut s = String::from("hello");

let r1 = &s;
let r2 = &s;
// let r3 = &mut s; // Esto fallará

println!("{}, {}", r1, r2);
```

### Seguridad de memoria
- **Manejo seguro de la memoria**
 - Rust garantiza seguridad de memoria sin un recolector de basura.
 - Los errores comunes como null pointers y dangling pointers están eliminados.

### Concurrency
- **Trabajos concurrentes seguros**
 - Rust facilita la programación concurrente segura usando el sistema de tipos.

```rust
use std::thread;

let handle = thread::spawn(|| {
    for i in 1..10 {
        println!("hi number {} from the spawned thread!", i);
    }
});

handle.join().unwrap();
```

- **Canales (channels) y hilos (threads)**
 - Los canales permiten la comunicación segura entre hilos.

```rust
use std::sync::mpsc;
use std::thread;

let (tx, rx) = mpsc::channel();

thread::spawn(move || {
    let val = String::from("hi");
    tx.send(val).unwrap();
});

let received = rx.recv().unwrap();
println!("Got: {}", received);
```

### Error Handling
- **Manejo de errores con Result y Option**
 - Result se usa para errores recuperables.
 - Option se usa para valores que pueden o no estar presentes.

```rust
fn divide(numerator: f64, denominator: f64) -> Result<f64, String> {
    if denominator == 0.0 {
        return Err(String::from("Cannot divide by zero"));
    }
    Ok(numerator / denominator)
}

let result = divide(4.0, 2.0);
match result {
    Ok(val) => println!("Result: {}", val),
    Err(e) => println!("Error: {}", e),
}
```

- **Uso de panic! para errores catastróficos**
 - panic! detiene el programa cuando ocurre un error grave.

```rust
fn main() {
    panic!("This is a panic");
}
```

### Macros
- **Introducción a macros**
 - Las macros permiten escribir código que genera otros fragmentos de código.
- **Definición y uso de macros**

```rust
macro_rules! say_hello {
    () => {
        println!("Hello!");
    };
}

fn main() {
    say_hello!();
}
```

## 1.4.3. ¿Qué podemos hacer con Rust?
### Desarrollo de sistemas
- **Creación de sistemas operativos y drivers**
 - Rust se usa en proyectos como Redox, un sistema operativo escrito en Rust.
- **Desarrollo de software de bajo nivel
 - Rust es ideal para escribir software que requiere un control preciso sobre el hardware.

### Aplicaciones web
 - **Servidores web y microservicios**
 - Frameworks como Actix y Rocket facilitan la creación de servidores web rápidos y seguros.

```rust
use actix_web::{web, App, HttpServer, Responder};

async fn greet() -> impl Responder {
    "Hello world!"
}

#[actix_web::main]
async fn main() -> std::io::Result<()> {
    HttpServer::new(|| {
        App::new()
            .route("/", web::get().to(greet))
    })
    .bind("127.0.0.1:8080")?
    .run()
    .await
}
```

### Herramientas de línea de comandos
 - **Creación de herramientas CLI rápidas y eficientes**
 - Con crates como structopt y clap, puedes crear herramientas CLI robustas.

```rust
use structopt::StructOpt;

#[derive(StructOpt)]
struct Cli {
    name: String,
}

fn main() {
    let args = Cli::from_args();
    println!("Hello, {}!", args.name);
}
```

### Desarrollo de juegos
 - **Introducción a librerías como Amethyst y Bevy**
 - Estas librerías proporcionan herramientas y motores para desarrollo de juegos en Rust.

```rust
use bevy::prelude::*;

fn main() {
    App::build()
        .add_plugins(DefaultPlugins)
        .add_startup_system(hello_world.system())
        .run();
}

fn hello_world() {
    println!("Hello, Bevy!");
}
```

### Análisis de datos y Machine Learning
- **Uso de crates como polars y ndarray para análisis de datos**
 - Estas crates permiten trabajar con datos de manera eficiente.

```rust
use polars::prelude::*;
use std::fs::File;

fn main() -> Result<()> {
    let file = File::open("data.csv").unwrap();
    let df = CsvReader::new(file).infer_schema(None).has_header(true).finish().unwrap();
    println!("{:?}", df);
}
```

- **Implementación de algoritmos de Machine Learning**
 - Crates como smartcore proporcionan herramientas para implementar algoritmos de machine learning.

```rust
use smartcore::linalg::naive::dense_matrix::DenseMatrix;
use smartcore::tree::decision_tree_classifier::DecisionTreeClassifier;

fn main() {
    let x = DenseMatrix::from_2d_array(&[
        &[2.0, 3.0],
        &[10.0, 15.0],
        &[5.0, 8.0],
        &[9.0, 10.0]
    ]);

    let y = vec![0, 1, 0, 1];

    let tree = DecisionTreeClassifier::fit(&x, &y, Default::default()).unwrap();
    let y_hat = tree.predict(&x).unwrap();

    println!("{:?}", y_hat);
}
```

