### Instalación de dependencias

[Link de serde](https://crates.io/crates/serde) que es un framework para serializar y deserializar estructuras en Rust
```bash
cargo add serde
```

o agregamos esto dentro del .toml

```toml
[dependencies]
serde = { version = "1.0", features = ["derive"] }
serde_json = "1.0"
```