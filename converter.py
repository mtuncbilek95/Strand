#!/usr/bin/env python3
"""
Script to update license headers in source files
Replaces old Mozilla Public License headers with custom LICENSE.md reference
"""

import os
import re
import argparse
from pathlib import Path

# Yeni lisans başlığı
NEW_LICENSE_HEADER = '''/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */'''

# Desteklenen dosya uzantıları
SUPPORTED_EXTENSIONS = {'.js', '.ts', '.jsx', '.tsx', '.java', '.c', '.cpp', '.h', '.hpp', '.cs', '.php', '.go', '.rust', '.rs', '.scala', '.kt'}

def find_license_block(content):
    """
    Dosya içeriğinde lisans bloğunu bulur
    Mozilla Public License veya benzer /* */ formatındaki lisans bloklarını arar
    """
    # Çok satırlı yorum bloğu pattern'i (/* ile başlayıp */ ile biten)
    pattern = r'/\*[\s\S]*?\*/'
    
    matches = list(re.finditer(pattern, content))
    
    for match in matches:
        block = match.group(0)
        
        # Mozilla Public License referansı içeriyorsa
        if ('Mozilla Public License' in block or 
            'MPL' in block or 
            'mozilla.org/MPL' in block or
            'This Source Code Form is subject to the terms' in block):
            return match.start(), match.end()
    
    return None, None

def update_license_header(file_path):
    """
    Tek bir dosyanın lisans başlığını günceller
    """
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            content = f.read()
        
        start_pos, end_pos = find_license_block(content)
        
        if start_pos is not None and end_pos is not None:
            # Eski lisans bloğunu yeni ile değiştir
            new_content = content[:start_pos] + NEW_LICENSE_HEADER + content[end_pos:]
            
            with open(file_path, 'w', encoding='utf-8') as f:
                f.write(new_content)
            
            print(f"Güncellendi: {file_path}")
            return True
        else:
            print(f"Lisans bloğu bulunamadı: {file_path}")
            return False
            
    except Exception as e:
        print(f"❌ Hata ({file_path}): {e}")
        return False

def scan_directory(directory, recursive=True):
    """
    Dizini tarar ve uygun dosyaları bulur
    """
    files_to_process = []
    
    if recursive:
        for root, dirs, files in os.walk(directory):
            # .git, node_modules, __pycache__ gibi dizinleri atla
            dirs[:] = [d for d in dirs if not d.startswith('.') and d not in ['node_modules', '__pycache__', 'dist', 'build']]
            
            for file in files:
                file_path = Path(root) / file
                if file_path.suffix.lower() in SUPPORTED_EXTENSIONS:
                    files_to_process.append(file_path)
    else:
        for file in os.listdir(directory):
            file_path = Path(directory) / file
            if file_path.is_file() and file_path.suffix.lower() in SUPPORTED_EXTENSIONS:
                files_to_process.append(file_path)
    
    return files_to_process

def main():
    parser = argparse.ArgumentParser(description='Update license headers in source files')
    parser.add_argument('directory', nargs='?', default='.', help='Directory to process (default: current directory)')
    parser.add_argument('--no-recursive', action='store_true', help='Don\'t process subdirectories')
    parser.add_argument('--dry-run', action='store_true', help='Show what would be changed without making changes')
    
    args = parser.parse_args()
    
    directory = Path(args.directory)
    if not directory.exists():
        print(f"Dizin bulunamadı: {directory}")
        return
    
    print(f"Tarama yapılıyor: {directory.absolute()}")
    print(f"Alt dizinler dahil: {'Evet' if not args.no_recursive else 'Hayır'}")
    print(f"Deneme modu: {'Evet' if args.dry_run else 'Hayır'}")
    print()
    
    # Desteklenen uzantıları göster
    print(f"Desteklenen dosya türleri: {', '.join(sorted(SUPPORTED_EXTENSIONS))}")
    print()
    
    files_to_process = scan_directory(directory, recursive=not args.no_recursive)
    
    if not files_to_process:
        print("İşlenecek dosya bulunamadı.")
        return
    
    print(f"Toplam {len(files_to_process)} dosya bulundu.")
    print()
    
    if args.dry_run:
        print("DENEME MODU - Aşağıdaki dosyalar işlenecek:")
        for file_path in files_to_process:
            try:
                with open(file_path, 'r', encoding='utf-8') as f:
                    content = f.read()
                start_pos, end_pos = find_license_block(content)
                if start_pos is not None:
                    print(f"{file_path}")
                else:
                    print(f"{file_path} (lisans bloğu yok)")
            except Exception as e:
                print(f"{file_path} (hata: {e})")
        return
    
    # Onay iste
    response = input("Devam etmek istiyor musunuz? (y/N): ")
    if response.lower() not in ['y', 'yes', 'evet', 'e']:
        print("İşlem iptal edildi.")
        return
    
    print()
    print("İşlem başlıyor...")
    print()
    
    updated_count = 0
    for file_path in files_to_process:
        if update_license_header(file_path):
            updated_count += 1
    
    print()
    print(f"Tamamlandı! {updated_count}/{len(files_to_process)} dosya güncellendi.")

if __name__ == '__main__':
    main()