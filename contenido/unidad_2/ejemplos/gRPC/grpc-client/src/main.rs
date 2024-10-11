use studentgrpc::student_client::StudentClient;
use studentgrpc::StudentRequest;

pub mod studentgrpc {
    tonic::include_proto!("studentgrpc");
}

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    let mut client = StudentClient::connect("http://[::1]:50051").await?;

    let request = tonic::Request::new(StudentRequest{
       name: "Alvaro Rust".into(),
       age: 25,
       faculty: "Ingenería".into(),
       discipline: 1, 
    });

    let response = client.get_student(request).await?;

    println!("RESPONSE={:?}", response);

    Ok(())
}