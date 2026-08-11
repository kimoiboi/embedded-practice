# Week 3 — Multimeter Fluency & Physical Builds

**Status:** Sim pass — Build 1 complete, Build 2 partial. Builds 3–4 pending. Bench pass pending.
**Simulator:** Tinkercad Circuits
**Meter (bench):** AstroAI AM33D, 2000-count, manual range
**Supply (bench):** HW-131 module — *faulty, replacement pending*
**Date started:**
**Date bench pass completed:**

---

## 0. How to use this file

Every results table has **two measured columns**: `Sim` and `Bench`. Fill the `Sim`
column now in Tinkercad. Leave `Bench` empty until you have working hardware, then
come back and fill it without changing anything else. The gap between those two
columns is the actual deliverable for this week.

Rows are tagged:

- `[SIM]` — Tinkercad reproduces this faithfully. Sim result is trustworthy.
- `[BENCH]` — Tinkercad **cannot** show this. The sim will give a clean, wrong,
  or meaningless answer. Record it anyway, note what the simulator claimed, and
  flag it for the hardware pass.

### What Tinkercad cannot teach you

Worth writing down now so the bench pass has a purpose:

| Real-world effect | Tinkercad's version |
|---|---|
| Resistor tolerance | None. A 220 Ω resistor is exactly 220.000 Ω. |
| Meter burden voltage | None. The ammeter is ideal — zero resistance. |
| Meter input impedance | Effectively infinite. Cannot load a circuit. |
| Manual ranging | None. No range selection, no overrange, no resolution limit. |
| Lead resistance | None. |
| Contact bounce | Not modeled. |
| Floating inputs | Not physical. A floating node does not drift or respond to touch. |
| Supply sag under load | Regulated ideal source. No sag. |
| LED part-to-part variation | Every red LED is identical. |

**Consequence:** in the sim, predicted and measured will agree to within rounding
on almost every row. That is not a result — it is the absence of one. The sim
pass verifies your *procedure*; the bench pass produces your *data*.

---

## 1. Formula reference

| Purpose | Formula |
|---|---|
| Ohm's law | `V = I × R` |
| Current from a measured voltage drop | `I = V_R / R` |
| LED resistor sizing | `R = (Vs − Vf) / If` |
| Power in a resistor | `P = I²R = V²/R = VI` |
| Series resistance | `R_total = R1 + R2 + …` |
| Parallel resistance | `1/R_total = 1/R1 + 1/R2 + …`  (two: `R1R2/(R1+R2)`) |
| Voltage divider (unloaded) | `Vout = Vs × R2/(R1+R2)` |
| Thévenin voltage | `Vth = Vout` unloaded |
| Thévenin resistance | `Rth = R1 ∥ R2` |
| Loaded divider output | `Vout = Vth × RL/(RL + Rth)` |
| KVL check | `Vs = ΣV_drops` around the loop |
| KCL check | `ΣI_in = ΣI_out` at a node |
| Signed percent error | `(measured − predicted) / predicted × 100` |

---

## 2. Tinkercad setup notes

- The **Power Supply** is not in the Basic components list — type "Power Supply"
  into the component search box. It has a voltage knob and a current display.
  Set it to **5.00 V**.
- Alternatively use a 9 V battery, but then your Vs is 9 V and all predictions change.
- The **Multimeter** has three modes: voltage, current, resistance. Voltage is
  the default. Change mode in the component inspector.
- **Stop the simulation before changing any component value.** Values are locked
  while running.
- `r` rotates a selected component clockwise, `Shift+R` counter-clockwise.
- Hovering over the breadboard highlights which holes are connected — use this
  the same way you would use a continuity beep on real hardware.
- **The Tinkercad pushbutton has redundant terminals:** 1a and 1b are internally
  connected, as are 2a and 2b. This mirrors the real 4-pin tactile switch and is
  the same trap — get the orientation wrong and the switch reads permanently closed.

### Bench-pass supply options (HW-131 is dead)

1. Arduino/Adafruit board **5V** (or **VUSB**) pin → + rail, **GND** → − rail,
   board powered from laptop USB. Regulated, free, adequate for ~15 mA.
2. 9 V battery + barrel adapter into a replacement module.
3. 7–9 V wall wart, 5.5 × 2.1 mm center-positive.

Whichever you use: **measure the actual rail voltage and use that number in every
prediction.** Never assume 5.00 V.

---

## 3. Bench conditions

Fill the `Sim` column with what Tinkercad reports. Fill `Bench` on the hardware pass.

| Item | Nominal | Sim | Bench | Range used (bench) | Notes |
|---|---|---|---|---|---|
| Lead resistance `[BENCH]` | 0 Ω | n/a | | Ω 200 | Probes shorted together |
| Supply, unloaded | 5.00 V | 5.00 V | | DCV 20 | Ideal source, no sag |
| Supply, loaded `[BENCH]` | — | | | DCV 20 | Sag under load |
| R (LED series) | 220 Ω | 220 Ω | | Ω 2000 | Sim: exact. Also ran 470 Ω, 1 kΩ, 2.2 kΩ, 96 Ω |
| R1 (divider top) | 1000 Ω | | | Ω 2000 | |
| R2 (divider bottom) | 2000 Ω | | | Ω 2000 | |
| R (pull resistor) | 10 kΩ | | | Ω 20k | |
| Pot, total resistance | 10 kΩ | | | Ω 20k | Wiper-to-end + end-to-wiper |
| LED Vf @ ~1 mA `[BENCH]` | — | n/a | | Diode mode | Meter tops out ~3 V open circuit |

**Breadboard map `[BENCH]`** — verify with continuity, don't trust the silkscreen:

- Column groups of 5: `[ ] confirmed`
- Center channel isolates the two halves: `[ ] confirmed`
- Power rails run full length / **split at midboard**: `[ ] ______________`

---

## 4. Build 1 — LED + series resistor ✅ COMPLETE (sim pass)

**Circuit:** `+ rail → R → LED anode → LED cathode → − rail`
**Simulated:** Tinkercad, red LED, ideal 5.00 V / 3.30 V power supply
**Date:**

### 4.1 Method

For each run: set Vs and R, start the sim, measure V across the resistor and V
across the LED with the multimeter in voltage mode. Compute current from the
resistor drop rather than reading it directly, so that every number traces back
to a voltage measurement and a known resistance.

Assumed forward voltage for all predictions: **Vf = 2.00 V**, taken from the
standard red/orange/yellow band of 1.8–2.2 V. This assumption is the subject of
the entire experiment.

> **Sourcing note:** the 1.8–2.2 V figure came from a general reference, not a
> manufacturer datasheet. For the bench pass, cite a real 5 mm red LED datasheet
> (Kingbright, Everlight, Lite-On) with the test current stated. "Vf = 2.0 V" is
> meaningless without the current it was measured at — which is precisely what
> section 4.4 demonstrates.

### 4.2 Resistor sizing

```
R = (Vs − Vf) / If        target If = 13.6 mA

5.0 V:  R = (5.0 − 2.0) / 0.0136 = 3.0 / 0.0136 = 221 Ω  → use 220 Ω
3.3 V:  R = (3.3 − 2.0) / 0.0136 = 1.3 / 0.0136 =  96 Ω  → use 96 Ω
```

The supply fell 34 % but the resistor had to fall 56 %. Vf is a fixed toll on the
loop, so what's left for the resistor — `Vs − Vf` — shrank from 3.0 V to 1.3 V,
a much larger proportional change than the supply itself.

### 4.3 Results — all runs

**Predicted** uses Vf = 2.00 V. **Corrected** re-runs the same formulas with the
*measured* Vf. All percent errors are signed, measured against the nominal
prediction.

| Vs | R | Pred V_R | Pred If | Pred P | Meas V_R | Meas Vf | Meas If | Meas P |
|---|---|---|---|---|---|---|---|---|
| 5.0 V | 220 Ω | 3.00 V | 13.64 mA | 40.9 mW | 2.98 V | 2.02 V | 13.55 mA | 40.4 mW |
| 5.0 V | 470 Ω | 3.00 V | 6.38 mA | 19.1 mW | 3.06 V | 1.94 V | 6.51 mA | 19.9 mW |
| 5.0 V | 1 kΩ | 3.00 V | 3.00 mA | 9.0 mW | 3.11 V | 1.89 V | 3.11 mA | 9.7 mW |
| 5.0 V | 2.2 kΩ | 3.00 V | 1.36 mA | 4.1 mW | 3.16 V | 1.84 V | 1.44 mA | 4.5 mW |
| 3.3 V | 96 Ω | 1.30 V | 13.54 mA | 17.6 mW | 1.28 V | 2.02 V | 13.33 mA | 17.1 mW |

**Signed percent error vs. nominal prediction:**

| Vs | R | % err V_R | % err Vf | % err If | % err P |
|---|---|---|---|---|---|
| 5.0 V | 220 Ω | −0.7 % | +1.0 % | −0.7 % | −1.3 % |
| 5.0 V | 470 Ω | +2.0 % | −3.0 % | +2.0 % | +4.0 % |
| 5.0 V | 1 kΩ | +3.7 % | −5.5 % | +3.7 % | +7.5 % |
| 5.0 V | 2.2 kΩ | +5.3 % | −8.0 % | +5.3 % | +11.0 % |
| 3.3 V | 96 Ω | −1.5 % | +1.0 % | −1.5 % | −3.1 % |

**Corrected predictions** (same formulas, measured Vf substituted):

| Vs | R | Corrected V_R | Corrected If | Measured If | % err vs corrected |
|---|---|---|---|---|---|
| 5.0 V | 220 Ω | 2.98 V | 13.55 mA | 13.55 mA | 0.0 % |
| 5.0 V | 470 Ω | 3.06 V | 6.51 mA | 6.51 mA | 0.0 % |
| 5.0 V | 1 kΩ | 3.11 V | 3.11 mA | 3.11 mA | 0.0 % |
| 5.0 V | 2.2 kΩ | 3.16 V | 1.44 mA | 1.44 mA | 0.0 % |
| 3.3 V | 96 Ω | 1.28 V | 13.33 mA | 13.33 mA | 0.0 % |

Every corrected prediction lands exactly. Ohm's law was never in question — the
Vf assumption was the only error in the model.

*(Exactness here is a property of the simulator, not a triumph. Tinkercad
resistors are exactly nominal and the supply is exactly regulated, so once Vf is
corrected there is nothing left to disagree. On the bench, tolerance and meter
loading will keep this column from reaching zero.)*

### 4.4 The finding — Vf is a function of current

Sorted by current, all runs pooled:

| If (measured) | Vf (measured) | Supply | R |
|---|---|---|---|
| 1.44 mA | 1.84 V | 5.0 V | 2.2 kΩ |
| 3.11 mA | 1.89 V | 5.0 V | 1 kΩ |
| 6.51 mA | 1.94 V | 5.0 V | 470 Ω |
| 13.33 mA | 2.02 V | 3.3 V | 96 Ω |
| 13.55 mA | 2.02 V | 5.0 V | 220 Ω |

**Two things fall out of this table.**

**1. Current changed by 9.4×; Vf changed by 0.18 V — under 10 %.** Each halving
of current costs roughly 50–80 mV of forward voltage. That near-flatness is the
diode's exponential I–V curve seen from the voltage axis, and it is why "Vf = 2 V"
is a workable engineering approximation despite being wrong at every single
operating point.

**2. Vf depends on current, not on supply voltage.** The 3.3 V run at 13.33 mA and
the 5.0 V run at 13.55 mA both produced Vf = 2.02 V, from supplies 1.7 V apart.
The LED does not know or care what the supply is — it only responds to the
current forced through it. This is the single most important result of Build 1.

*(A log-linear fit of Vf against ln(If) would give the diode ideality factor,
but Tinkercad reports only 10 mV resolution and the steps here are ~50 mV, so the
fit would carry ~20 % uncertainty. Defer to the bench pass, where the AM33D's
2000 mV range gives 1 mV resolution.)*

### 4.5 Error analysis

The error is **not noise — it is monotonic and signed.** As R rises, current
falls, real Vf falls, and the error grows in a fixed direction:

| R | Meas Vf | Vf error | If error |
|---|---|---|---|
| 220 Ω | 2.02 V | +1.0 % | −0.7 % |
| 470 Ω | 1.94 V | −3.0 % | +2.0 % |
| 1 kΩ | 1.89 V | −5.5 % | +3.7 % |
| 2.2 kΩ | 1.84 V | −8.0 % | +5.3 % |

**The signs are always opposite, and the mechanism is arithmetic.** Vf and V_R
share a fixed budget of 5.00 V. Underestimating Vf by 0.16 V hands that same
0.16 V to the resistor, so measured current runs high by exactly that amount over
R. Overestimate Vf and it runs low.

At 220 Ω the assumption was nearly correct because 220 Ω was *sized* for ~13.6 mA,
which is where Vf actually sits at 2.02 V. The assumption degrades as the operating
point moves away from where it was calibrated. **An assumed constant is only valid
at the operating point it was taken from.**

Two consistency checks worth noting:

- `% err V_R` and `% err If` match in every row, as they must — `If = V_R/R` with
  R exact, so the errors are the same number.
- `% err P ≈ 2 × % err If` in every row, as it must — `P = I²R`, so a squared
  quantity carries roughly double the fractional error.

Both confirm the arithmetic is internally consistent and the discrepancy has one
single source, not several.

### 4.6 Power check

| R | P dissipated | % of ¼ W rating |
|---|---|---|
| 220 Ω | 40.4 mW | 16 % |
| 470 Ω | 19.9 mW | 8 % |
| 1 kΩ | 9.7 mW | 4 % |
| 2.2 kΩ | 4.5 mW | 2 % |
| 96 Ω | 17.1 mW | 7 % |

Worst case is 16 % of rating — comfortable margin, no thermal concern. Peak
current 13.55 mA is also well under the ~20 mA indicator-LED limit.

For reference, a ¼ W resistor would need `√(0.25/220) = 33.7 mA` to reach its
rating at 220 Ω — about 2.5× the operating current here.

### 4.7 KVL verification

| Vs | R | V_R | Vf | Sum | Residual |
|---|---|---|---|---|---|
| 5.0 V | 220 Ω | 2.98 | 2.02 | 5.00 | 0.00 |
| 5.0 V | 470 Ω | 3.06 | 1.94 | 5.00 | 0.00 |
| 5.0 V | 1 kΩ | 3.11 | 1.89 | 5.00 | 0.00 |
| 5.0 V | 2.2 kΩ | 3.16 | 1.84 | 5.00 | 0.00 |
| 3.3 V | 96 Ω | 1.28 | 2.02 | 3.30 | 0.00 |

All residuals zero. Expected in an ideal simulator; on the bench, expect a few mV
of residual and treat anything larger as a wiring fault, not a discovery.

### 4.8 `[BENCH]` Burden voltage experiment

**Cannot be done in Tinkercad** — the simulated ammeter has zero resistance.

Measure the *same* current on the **200 mA** range, then the **20 mA** range. The
lower range uses a larger internal shunt, so it should read low.

The AM33D specifies a 200 mV drop at full scale, implying roughly:
- 200 mA range → ~1 Ω shunt → ~0.5 % error in a 220 Ω circuit
- 20 mA range → ~10 Ω shunt → ~4.5 % error in a 220 Ω circuit

| Range | Predicted reading | Measured | Implied shunt R |
|---|---|---|---|
| 200 mA | | | |
| 20 mA | | | |

### 4.9 Discussion

Predicted current using Vf = 2.00 V was within 0.7 % at 220 Ω but drifted to
5.3 % at 2.2 kΩ. The cause was not the arithmetic and not the resistor — it was
the assumption that forward voltage is constant. Measured Vf ranged from 1.84 V
to 2.02 V across a 9.4× current sweep, and every deviation from the assumed 2.00 V
transferred directly onto the resistor, since the two drops must sum to the supply.
Substituting measured Vf back into the prediction eliminated the error entirely at
every operating point, confirming a single error source.

The result that generalizes furthest is that Vf tracks current, not supply
voltage: the 3.3 V and 5.0 V runs at ~13.4 mA produced identical 2.02 V readings.
The LED responds to the current forced through it, which is why the current-limiting
resistor — not the supply — is the design lever.

The practical consequence for later builds is that a datasheet Vf figure is only
usable alongside the test current it was measured at, and that sizing a resistor
from a Vf quoted at 20 mA will give the wrong current if the target is 2 mA.

**Carry to bench pass:**
- Repeat with real components; expect tolerance and meter loading to prevent the
  corrected column from reaching 0.0 %.
- Measure Vf in diode mode (~1 mA) as an additional low-current data point.
- Use the 2000 mV range for Vf readings under 2 V — 1 mV resolution instead of 10 mV.
- Test a blue or white LED at 3.3 V and confirm it fails to light (Vf ≈ 3.2 V
  leaves ~0.1 V of headroom).

---

## 5. Build 2 — 3.3 V divider, loaded vs. unloaded ⚠️ SIM PASS PARTIAL

**Circuit:** `+ rail → R1 (1 kΩ) → node → R2 (2 kΩ) → − rail`, Vout measured at the node.
Load `RL` connects from the node to the − rail, **in parallel with R2**.
**Simulated:** Tinkercad, ideal 5.00 V supply
**Date:**

### 5.1 Design and predictions

The name refers to the **output**, not the input. Supply stays at 5.00 V; the
resistor ratio produces 3.3 V at the node.

```
Need  R2/(R1+R2) = 3.3/5 = 0.66  →  R2 ≈ 2 × R1
Chose R1 = 1 kΩ, R2 = 2 kΩ

Vout(unloaded) = 5 × 2000/3000        = 3.333 V
Vth            = Vout(unloaded)       = 3.333 V
Rth            = R1 ∥ R2 = 2e6/3000   = 666.7 Ω
I(unloaded)    = 5/3000               = 1.667 mA
```

**R1 and R2 are in SERIES.** That is what makes it a divider — one current path,
so the two resistors split the supply by their ratio. Parallel only enters when
`RL` is added, and then only between `R2` and `RL`.

### 5.2 Predictions — both methods

Method 1 collapses `R2 ∥ RL` and re-runs the divider formula. Method 2 uses the
Thévenin form. They must agree; agreement is the arithmetic self-check.

| RL | R2 ∥ RL | R_total | I | V across R1 | **Vout** (method 1) | **Vout** (method 2) |
|---|---|---|---|---|---|---|
| open | 2000 Ω | 3000 Ω | 1.667 mA | 1.667 V | **3.333 V** | 3.333 V |
| 100 kΩ | 1960.8 Ω | 2960.8 Ω | 1.689 mA | 1.689 V | **3.311 V** | 3.311 V |
| 10 kΩ | 1666.7 Ω | 2666.7 Ω | 1.875 mA | 1.875 V | **3.125 V** | 3.125 V |
| 1 kΩ | 666.7 Ω | 1666.7 Ω | 3.000 mA | 3.000 V | **2.000 V** | 2.000 V |

Both methods agree to four figures on every row. ✅

### 5.3 Results

| RL | Pred Vout | Sim Vout | Bench | Pred I | Sim I | % err sim |
|---|---|---|---|---|---|---|
| open | 3.333 V | | | 1.667 mA | | |
| 100 kΩ | 3.311 V | *invalid — see 5.6* | | 1.689 mA | *invalid* | |
| 10 kΩ | 3.125 V | **3.12 V** | | 1.875 mA | **1.87 mA** | ~0 % |
| 1 kΩ | 2.000 V | | | 3.000 mA | | |

**Supporting measurement, 10 kΩ run:** Vs = 4.99 V, V across R1 = 1.87 V,
Vout = 3.12 V. KVL: `1.87 + 3.12 = 4.99` ✓ — sums to the *measured* supply, not
to the nominal 5.00.

> **Rows still to fill:** unloaded, 100 kΩ (re-run after the current-limit fix),
> and 1 kΩ. The 10 kΩ row matched prediction to display resolution, so the method
> is validated; the remaining rows are collection, not investigation.

### 5.4 The finding — droop is governed by RL/Rth

| RL | RL / Rth | Vout | Droop from unloaded |
|---|---|---|---|
| open | ∞ | 3.333 V | 0 % |
| 100 kΩ | 150× | 3.311 V | **0.66 %** |
| 10 kΩ | 15× | 3.125 V | **6.25 %** |
| 1 kΩ | 1.5× | 2.000 V | **40.0 %** |

Droop is exactly `Rth / (RL + Rth)` — one expression covering every row. This is
why `Rth` is worth computing before any load exists: it is a property of the
divider, not of the load, and it predicts the sag for any load in one step.

**Rule of thumb:** the load must be roughly 10× `Rth` or larger to keep droop
under ~10 %. A 1 kΩ load against a 667 Ω source resistance fails this badly and
costs 40 % of the output.

### 5.5 KCL at the node (1 kΩ load) `[to measure]`

Build 1 was a single loop, so only KVL applied. This is the first node with three
branches and the first place KCL can be demonstrated.

| Branch | Direction | Predicted | Sim | Bench |
|---|---|---|---|---|
| Through R1 | in | 3.00 mA | | |
| Through R2 | out | 1.00 mA | | |
| Through RL | out | 2.00 mA | | |

`1.00 + 2.00 = 3.00` — current in equals current out. RL is half the resistance of
R2, so it takes twice the current at the same 2.00 V.

Measure each branch **in series** — break the path and insert the meter — rather
than computing `V/R`. Doing it three times is the point.

### 5.6 Incident: supply entered constant-current mode

**Symptom:** with the 100 kΩ load connected, supply read 4.94 V instead of 5.00 V
and current sat pinned at 1.67 mA.

**Cause:** the supply's *current limit* had been set to 0.00167 A — exactly the
unloaded draw. Adding the load raised demand to 1.689 mA, exceeding the limit, so
the supply reduced its output voltage until current fell back to the ceiling.
This is **constant-current (CC) mode**, the normal behaviour of any bench supply,
not a circuit fault and not a simulator quirk.

**Fix:** raise the current limit well above expected draw (50–100 mA here). Worth
noting the 1 kΩ run draws 3.00 mA — nearly double the original limit — so the
fault would have recurred and corrupted that row too.

**Why the limit exists:** on real hardware it is protection. Set just above
expected draw, a wiring mistake causes the supply to drop voltage instead of
dumping current into a short and destroying parts.

**Data affected:** the 100 kΩ row was taken under CC and is invalid. Re-run.

### 5.7 Power check

| Condition | Resistor | P | % of ¼ W |
|---|---|---|---|
| Unloaded | R1 | 2.78 mW | 1.1 % |
| Unloaded | R2 | 5.56 mW | 2.2 % |
| 1 kΩ load | R1 | 9.00 mW | 3.6 % |
| 1 kΩ load | R2 | 2.00 mW | 0.8 % |
| 1 kΩ load | RL | 4.00 mW | 1.6 % |

All negligible. This divider wastes almost no power — which, as 5.8 shows, is
precisely why it cannot hold its voltage.

### 5.8 The design tradeoff — what stiffness costs

*Question posed in 5.4: what would Rth have to be for a 1 kΩ load to droop under 1 %?*

```
Rth/(1000 + Rth) < 0.01   →   Rth < 10.1 Ω

Holding the 2:1 ratio:  Rth = 2·R1/3 = 10  →  R1 = 15 Ω, R2 = 30 Ω
```

| Design | Rth | Droop @ 1 kΩ | Standing current | P in R1 | P in R2 |
|---|---|---|---|---|---|
| 1 kΩ / 2 kΩ | 667 Ω | 40 % | 1.67 mA | 2.8 mW | 5.6 mW |
| 15 Ω / 30 Ω | 10 Ω | 0.99 % | **111 mA** | 185 mW | **370 mW** |
| 10 Ω / 20 Ω | 6.7 Ω | 0.66 % | **167 mA** | 278 mW | **556 mW** |

**Both stiff designs exceed a ¼ W resistor rating on R2.** They also burn 111–167 mA
continuously whether anything is connected or not — on a battery-powered device
that is a flat battery in hours while doing nothing.

**There is no setting that gives both.** Low Rth means a stiff output and wasted
power; high Rth means efficient and useless under load. The ratio sets the
voltage; the absolute values set the tradeoff. Two multiplications produce the
entire argument.

This is why voltage regulators exist: a regulator holds its output *actively*,
correcting as the load changes, instead of passively splitting whatever is there.
A divider's output is only as good as its assumption about the load, and a real
load is not a fixed resistance — a sensor draws different current idle vs.
transmitting, so its effective resistance moves and Vout wanders with it.

### 5.9 `[BENCH]` Meter loading experiment

**Cannot be done in Tinkercad** — the simulated voltmeter has infinite input
impedance and will report the ideal value.

Rebuild the same 1:2 ratio with **1 MΩ / 2 MΩ**. The AM33D's ~10 MΩ input then
sits in parallel with the 2 MΩ leg and visibly drags the reading down. Same
`R2 ∥ RL` mathematics as this build, except the meter itself is the load.

| Divider | Predicted (ideal) | Predicted (with 10 MΩ meter) | Bench |
|---|---|---|---|
| 1 kΩ / 2 kΩ | 3.333 V | | |
| 1 MΩ / 2 MΩ | 3.333 V | | |

Hint: `2 MΩ ∥ 10 MΩ = 1.667 MΩ`, so `Vout = 5 × 1.667/(1 + 1.667)`.

### 5.10 Discussion

*Fill after the remaining rows. Points to cover: predicted and measured agreed to
display resolution on the 10 kΩ run, confirming the model; droop follows
`Rth/(RL+Rth)` across three orders of magnitude of load; the divider fails not
when idle but at the moment it is asked to do its job; and the stiffness/efficiency
tradeoff has no resolution within the divider topology, which is the motivation
for active regulation.*

**Bench-pass note:** 2 kΩ is not a standard kit value. Use **two 1 kΩ resistors in
series** for R2 — exact value, plus a free demonstration of series addition.
Measure the pair end-to-end before wiring.

---

## 6. Build 3 — Button + pull resistor (GPIO input before there's a GPIO)

### 6.1 Pull-down

**Circuit:** `+ rail → button → node → 10 kΩ → − rail`. Measure node to − rail.

| Button state | Predicted | Sim | Bench |
|---|---|---|---|
| Open | 0 V | | | 
| Pressed | 5 V | | |

### 6.2 Pull-up

**Circuit:** `+ rail → 10 kΩ → node → button → − rail`. Measure node to − rail.

| Button state | Predicted | Sim | Bench |
|---|---|---|---|
| Open | 5 V | | |
| Pressed | 0 V | | |

**Write out:** why the logic inverts, and which configuration is more common on
real microcontrollers (and why — think about internal pull-ups and noise immunity).

### 6.3 Current through the pull resistor

| Config | State | Predicted I | Sim | Bench |
|---|---|---|---|---|
| Pull-down | Pressed | 0.5 mA | | |
| Pull-down | Open | 0 mA | | |
| Pull-up | Pressed | 0.5 mA | | |
| Pull-up | Open | 0 mA | | |

Note which state burns current. This matters for battery-powered designs.

### 6.4 `[BENCH]` Floating input

**Cannot be done meaningfully in Tinkercad** — an unconnected node in the
simulator is not physical and won't drift.

Remove the pull resistor entirely. Measure the node.

- Reading, undisturbed: `______`
- Reading, finger near the wire: `______`
- Reading, finger touching the wire: `______`

Then wire the node to a digital input pin, `digitalRead()` in a tight loop, and
print. Compare a floating pin to a pulled one.

- Floating pin, transitions per second: `______`
- Pulled pin, transitions per second: `______`

**This is the entire justification for pull resistors, in one measurement.**

### 6.5 `[BENCH]` Switch bounce — deferred

Not visible on a DMM and not modeled in Tinkercad. Note as a known unknown.
Revisit with a scope (MIX makerspace) or by counting transitions in a tight
polling loop with `micros()` timestamps.

---

## 7. Build 4 — Potentiometer as a variable divider

**Circuit:** outer pins to + rail and − rail, wiper to meter.

### 7.1 Pot characterization (unpowered)

| Measurement | Predicted | Sim | Bench |
|---|---|---|---|
| End-to-end resistance | 10 kΩ | | |
| Wiper-to-A at midpoint | 5 kΩ | | |
| Wiper-to-B at midpoint | 5 kΩ | | |
| Sum of the two | 10 kΩ | | |

*Pots are commonly ±20 %. A "10 k" pot reading 9.1 k is normal, not a fault.*

### 7.2 Unloaded sweep

| Position | Predicted Vout | Sim | Bench |
|---|---|---|---|
| 0 % | 0.00 V | | |
| 25 % | 1.25 V | | |
| 50 % | 2.50 V | | |
| 75 % | 3.75 V | | |
| 100 % | 5.00 V | | |

### 7.3 Loaded sweep (1 kΩ from wiper to − rail)

`Rth at the wiper = R_total × x(1−x)`, maximum at midpoint = `R_total/4 = 2.5 kΩ`.

| Position | Rth | Vth | Predicted Vout | Sim | Bench |
|---|---|---|---|---|---|
| 0 % | 0 Ω | 0.00 V | 0.00 V | | |
| 25 % | 1875 Ω | 1.25 V | 0.435 V | | |
| 50 % | 2500 Ω | 2.50 V | 0.714 V | | |
| 75 % | 1875 Ω | 3.75 V | 1.304 V | | |
| 100 % | 0 Ω | 5.00 V | 5.00 V | | |

**The key observation:** the curve sags *most in the middle*, because that's
where source impedance peaks. Same lesson as Build 2, now as a shape instead of
a single number. Sketch both curves on the same axes.

### 7.4 Wiper → ADC

Wire the wiper to an analog input. Compare ADC counts against the meter.

| Position | Meter V | ADC counts | Counts × (Vref/max) | Difference |
|---|---|---|---|---|
| 0 % | | | | |
| 25 % | | | | |
| 50 % | | | | |
| 75 % | | | | |
| 100 % | | | | |

---

## 8. Skill tile: continuity check

`[BENCH]` — Tinkercad has no continuity beeper. Hovering to highlight connected
holes is the closest analogue.

Log each use:

| # | What I traced | Found | Outcome |
|---|---|---|---|
| 1 | Breadboard column groups | | |
| 2 | Center channel isolation | | |
| 3 | Power rail split at midboard | | |
| 4 | Tactile switch pin pairs | | |
| 5 | | | |

**Tile complete when:** you have used continuity to find at least one real wiring
fault you would not have found by inspection.

---

## 9. Week summary

### 9.1 Sim vs. bench divergence

*Fill after the hardware pass. For each build, where did Tinkercad and reality
disagree, and was the disagreement explainable from a known physical effect?*

| Build | Largest sim/bench gap | Cause | Explainable? |
|---|---|---|---|
| 1 | *pending bench pass* — sim showed 0.0 % vs corrected prediction; bench should not | Tolerance, meter burden, lead R | |
| 2 | *pending* — CC-mode incident logged in 5.6 | Supply current limit, not circuit | Yes |
| 3 | | | |
| 4 | | | |

### 9.2 Reporting discipline notes

- Keep percent error **signed**. Consistent signs across rows indicate a
  systematic effect; random signs indicate noise.
- Match significant figures to the instrument. The AM33D at 2000 counts gives
  **three** digits on most ranges, four on the 2000 mV range. Report percent
  error to **one decimal place**.
- On DCV 20, resolution is 10 mV, so a 4.98 V reading carries ±0.2 % before
  anything has gone wrong. **Anything under ~0.5 % on that range is noise, not a
  finding.** Write "within meter resolution" and move on.
- Tinkercad has no resolution limit, so sim values will look far more precise
  than they are meaningful. Do not report sim results to more digits than the
  bench pass could resolve.

### 9.3 Carry-forward

- [x] Build 1 sim pass complete
- [ ] Build 2: re-run 100 kΩ row after CC fix; collect unloaded + 1 kΩ + KCL
- [ ] Builds 3–4 sim pass
- [ ] Replacement power supply sourced
- [ ] Bench pass completed for all four builds
- [ ] MIX soldering/electronics workshop (unlocks scope + function generator)
- [ ] Switch bounce measurement — deferred to scope access
- [ ] Week 4 prep
