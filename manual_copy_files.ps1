# Manual File Copy Script for Displacement Mapping Project
# Run this from PowerShell in your displacement_mapping_hw directory

Write-Host "=== Copying Project Files ===" -ForegroundColor Cyan

# Define base paths
$hwFolder = "C:\Users\davin\OneDrive\Documents\AAA_Ohio_University\fall25\graphics\displacement_mapping_hw"
$auburnBase = "C:\Users\davin\OneDrive\Documents\AAA_Ohio_University\fall25\graphics\aburn\usr"

# Create directories
Write-Host "`nCreating directories..." -ForegroundColor Yellow
New-Item -ItemType Directory -Path "$hwFolder\src" -Force | Out-Null
New-Item -ItemType Directory -Path "$hwFolder\shaders" -Force | Out-Null
New-Item -ItemType Directory -Path "$hwFolder\images" -Force | Out-Null
New-Item -ItemType Directory -Path "$hwFolder\docs" -Force | Out-Null
Write-Host "  Directories created!" -ForegroundColor Green

# Copy source files
Write-Host "`nCopying C++ source files..." -ForegroundColor Yellow
$srcFiles = @(
    "GLViewdisplacement_grid.h",
    "GLViewdisplacement_grid.cpp",
    "GLSLShaderDisplacement.h",
    "GLSLShaderDisplacement.cpp"
)

foreach ($file in $srcFiles) {
    $source = "$auburnBase\usrModules\displacement_grid\$file"
    if (Test-Path $source) {
        Copy-Item $source "$hwFolder\src\$file" -Force
        Write-Host "  ✓ Copied $file" -ForegroundColor Green
    } else {
        Write-Host "  ✗ Not found: $file" -ForegroundColor Red
    }
}

# Copy shader files
Write-Host "`nCopying shader files..." -ForegroundColor Yellow
$shaderFiles = @("displacement.vert", "displacement.frag")
foreach ($file in $shaderFiles) {
    $source = "$auburnBase\shared\mm\shaders\$file"
    if (Test-Path $source) {
        Copy-Item $source "$hwFolder\shaders\$file" -Force
        Write-Host "  ✓ Copied $file" -ForegroundColor Green
    } else {
        Write-Host "  ✗ Not found: $file" -ForegroundColor Red
    }
}

# Copy image
Write-Host "`nCopying images..." -ForegroundColor Yellow
$imgSource = "$auburnBase\shared\mm\images\concentric_circles.jpg"
if (Test-Path $imgSource) {
    Copy-Item $imgSource "$hwFolder\images\concentric_circles.jpg" -Force
    Write-Host "  ✓ Copied concentric_circles.jpg" -ForegroundColor Green
} else {
    Write-Host "  ✗ Not found: concentric_circles.jpg" -ForegroundColor Red
}

# Move existing markdown files to docs (except README.md)
Write-Host "`nOrganizing documentation..." -ForegroundColor Yellow
$mdFiles = Get-ChildItem -Path $hwFolder -Filter "*.md" -File | Where-Object { $_.Name -ne "README.md" }
foreach ($file in $mdFiles) {
    Move-Item $file.FullName "$hwFolder\docs\$($file.Name)" -Force
    Write-Host "  ✓ Moved $($file.Name) to docs\" -ForegroundColor Green
}

Write-Host "`n=== Done! ===" -ForegroundColor Cyan
Write-Host "Files have been organized. Now run:" -ForegroundColor Yellow
Write-Host "  git add ."
Write-Host "  git commit -m 'Add source files, shaders, and images'"
