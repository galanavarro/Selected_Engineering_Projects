# Biomedical Signal Analysis

Python projects exploring how sampling and filtering affect signal interpretation, with an application to ECG analysis and heart-rate estimation.

## Projects

| Project | Main topics | Notebook |
|---|---|---|
| ECG Analysis | Signal visualisation, FFT, Butterworth filtering, R-peak detection and heart-rate estimation | [Open notebook](ecg_analysis/ecg_analysis.ipynb) |
| Sampling & Reconstruction | Discrete sampling, Nyquist criterion and sinc interpolation | [Open notebook](sampling_and_reconstruction.ipynb) |
| Aliasing Analysis | Effects of insufficient sampling on apparent signal frequency | [Open notebook](aliasing_analysis.ipynb) |
| Digital Filtering | Frequency analysis and FIR/IIR filtering approaches | [Open notebook](digital_filtering.ipynb) |

## ECG Analysis

The ECG workflow covers time- and frequency-domain visualisation, low-pass Butterworth filtering and comparison of the original and filtered signals. R-peak detection and interbeat intervals are used to estimate heart rate.

The notebook includes analysis of selected signal segments and automated peak detection using SciPy. The notebook and its input recording, `ecg_p5.npy`, are located in `ecg_analysis/`. Additional `.npy` files contain exported analysis outputs. A file named `hrv_Gala_Navarro.npy` retains its original coursework filename; an instantaneous heart-rate series alone should not be interpreted as a complete heart-rate variability assessment.

## Sampling & Reconstruction

Synthetic signals containing several frequency components are sampled and reconstructed using sinc interpolation. The analysis explores the relationship between signal bandwidth and sampling frequency, as well as the conditions required for meaningful reconstruction.

## Aliasing Analysis

Comparisons of signals above and below the Nyquist frequency demonstrate how insufficient sampling changes their apparent frequency. These examples illustrate why sampling settings matter when interpreting sensor recordings: a plausible-looking waveform may not represent the original signal correctly.

## Digital Filtering

FFT-based signal analysis and digital filter design examples cover FIR and IIR approaches. Comparisons examine frequency selectivity, filter order and the effect of filtering on the waveform. The notebook includes low-pass, high-pass and band-pass filtering examples.

## Tools

Python · NumPy · SciPy · Matplotlib · Jupyter Notebook

## Running the Notebooks

Install the dependencies:

```bash
pip install -r requirements.txt
```

Launch Jupyter:

```bash
jupyter notebook
```

Open a notebook and run its cells in order. Some exercises request parameters through interactive prompts.

For the ECG project, keep `ecg_p5.npy` alongside `ecg_analysis.ipynb` and use `ecg_analysis/` as the working directory when running it. No dataset download is required for the synthetic-signal notebooks.

## Background and Scope

Coursework for Biomedical Signal Processing at Universidad Politécnica de Cartagena. The notebooks contain code, visualisations and explanations of the analysis. Some original comments and explanations are in Spanish.

These are educational projects, not clinically validated tools. Signal interpretations and heart-rate estimates should be understood within that scope. Saved notebook outputs record previous runs.
