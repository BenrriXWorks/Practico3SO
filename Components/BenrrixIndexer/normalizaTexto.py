import os
import unicodedata
import sys
import concurrent.futures
import codecs
import re  # Agregar la importación de re

# Elimina los caracteres no alfabéticos, incluyendo las tabulaciones (\t), y convierte a minúsculas
def clean_text(text):
    # Cambiar los caracteres con tildes por letras normales
    cleaned_text = ''.join(c for c in unicodedata.normalize('NFD', text) if unicodedata.category(c) != 'Mn')
    # Eliminar caracteres no alfabéticos y convertir a minúsculas
    cleaned_text = ''.join(c.lower() if c.isalnum() or c.isspace() or c == '\t' else ' ' for c in cleaned_text)
    # Eliminar caracteres invisibles y reemplazarlos por espacios en blanco
    cleaned_text = re.sub(r'[\x00-\x1F\x7F-\x9F]', ' ', cleaned_text)
    return cleaned_text

def process_file(input_path, output_path):
    try:
        # Intentar abrir el archivo con utf-8
        try:
            with codecs.open(input_path, 'r', encoding='utf-8') as input_file:
                text = input_file.read()
        except UnicodeDecodeError:
            # Si falla, intentar abrirlo con latin-1
            with codecs.open(input_path, 'r', encoding='latin-1') as input_file:
                text = input_file.read()

        cleaned_text = clean_text(text)

        with codecs.open(output_path, 'w', encoding='utf-8') as output_file:
            output_file.write(cleaned_text)
    except Exception as e:
        print(f'Error al procesar el archivo {input_path}: {str(e)}')

def process(paths):
    # Crear la carpeta "Processed" si no existe
    os.makedirs("Processed", exist_ok=True)

    with concurrent.futures.ThreadPoolExecutor(max_workers=os.cpu_count()) as executor:
        futures = [executor.submit(process_file, os.path.abspath(path.strip('"')), os.path.join("Processed", os.path.basename(path.strip('"')))) for path in paths]

        # Esperar a que todos los archivos se procesen
        concurrent.futures.wait(futures)

if __name__ == "__main__":
    archivos = sys.argv[1:]
    process(archivos)