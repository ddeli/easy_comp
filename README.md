# Projektbeschreibung
A simple mono compressor external for Pure Data

#Installation:
git clone https://github.com/cbinner/easy_comp && cd easy_comp && make

Possible future enhancements:
* add make-up gain support
* don't ignore negative peaks for triggering compression
* support stereo/multichannel input
* implement lookahead function in order to catch fast peaks
* change input format for attack/release time from samples to ms (this implies using the current samplerate)
* improve signal quality for short attack times
* add soft knee option

* catch inter sample peaks (relevant if used as a limiter)
