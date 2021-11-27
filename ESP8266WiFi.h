# Single build under Windows to ensure the Win toolchain is good.
  build-windows:
    name: Windows
    runs-on: windows-latest
    steps:
    - uses: actions/checkout@v2
      with:
        submodules: true
    - uses: actions/setup-python@v2
      with:
        python-version: '3.x'
    - name: Cache Windows toolchain
      id: cache-windows
      uses: actions/cache@v2
      with:
        path: ./tools/dist
        key: ${{ runner.os }}-${{ hashFiles('package/package_esp8266com_index.template.json', 'tests/common.sh') }}
    - name: Build Sketch
      env:
        TRAVIS_BUILD_DIR: ${{ github.workspace }}
        TRAVIS_TAG: ${{ github.ref }}
        WINDOWS: 1
        BUILD_PARITY: custom
        mod: 500
        rem: 1
      run: |
        # Windows has python3 already installed, but it's called "python".
        # Copy python.exe to the proper name so scripts "just work".
        try { Get-Command python3 } catch { copy (get-command python).source (get-command python).source.Replace("python.exe", "python3.exe") }
        bash ./tests/build.sh
