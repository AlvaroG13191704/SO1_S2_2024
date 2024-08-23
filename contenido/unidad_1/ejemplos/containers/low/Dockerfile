# Dockerfile para un contenedor de bajo consumo
FROM python:3.9-slim

RUN pip install flask

COPY low.py /low.py

CMD ["python", "/low.py"]
