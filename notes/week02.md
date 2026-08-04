# Week 2 Notes — Real Components: Ratings, Time, and Semiconductors

**Source:** All About Circuits — Vol. I Ch. 2 §2.5 + Resistor Color Codes appendix, Vol. I Ch. 13 (Capacitors), Vol. I Ch. 16 (RC and L/R Time Constants), Vol. III Ch. 3 (Diodes & Rectifiers), Vol. III Ch. 4 (Bipolar Junction Transistors), Vol. III Ch. 6 (IGFETs / MOSFETs). Regulator and schematic-literacy material is **plan-note gap-filler** — assembled from datasheets and reference designs, not from a single chapter.

**Habit:** every worked example gets rebuilt in Falstad. Predict on paper → simulate → reconcile. The prediction/measurement/delta table *is* the deliverable; the circuits are just how you generate it.

**Week 1 → Week 2 shift:** Week 1 was ideal resistors obeying linear rules. Week 2 is where components start having **ratings** (they can be destroyed), **memory** (capacitors carry state across time), and **non-linear behavior** (diodes and transistors break Ohm's Law by design). Every "component" from now on is a device with a datasheet, not a number.

---

## Chapter A — Resistors in the Real World

### A.1 The color code

Reading bands is mechanical once you accept that the sequence is **digits → multiplier → tolerance**.

| Color | Digit | Multiplier | Tolerance |
|---|---|---|---|
| Black | 0 | ×1 | — |
| Brown | 1 | ×10 | ±1% |
| Red | 2 | ×100 | ±2% |
| Orange | 3 | ×1k | — |
| Yellow | 4 | ×10k | — |
| Green | 5 | ×100k | ±0.5% |
| Blue | 6 | ×1M | ±0.25% |
| Violet | 7 | ×10M | ±0.1% |
| Gray | 8 | — | ±0.05% |
| White | 9 | — | — |
| Gold | — | ×0.1 | ±5% |
| Silver | — | ×0.01 | ±10% |
| *(none)* | — | — | ±20% |

- **4-band:** digit · digit · multiplier · tolerance. **5-band:** digit · digit · digit · multiplier · tolerance (the extra digit is a precision part, usually ±1%).
- The three you'll see constantly, memorize as shapes not sequences:
  - **brown-black-red-gold** = 1 kΩ ±5%
  - **orange-orange-brown-gold** = 330 Ω ±5%
  - **yellow-violet-red-gold** = 4.7 kΩ ±5% (the 4k7 from Week 1)
- **Which end do you start from?** The tolerance band (gold/silver) is the one that's *set apart* by a wider gap, and it goes on the right. If both ends look ambiguous, there's no shame in the meter — but Ω-mode on a **dead, out-of-circuit** part only (Week 1 §3.9).
- ⚠️ **In-circuit measurement lies.** A resistor soldered into a board reads its own value *in parallel with every other path across it*. Always lower than expected, never higher. Lift one leg or measure before assembly.
- **CS anchor:** the color code is a base-10 float — two mantissa digits and an exponent. The 5-band is just extra mantissa precision. Same trade as float32 vs float64.

### A.2 Tolerance

- ±5% on "330 Ω" means anything in **313.5–346.5 Ω** is a conforming part. That's not a defect; that's the contract.
- **Design so tolerance doesn't matter.** LED current-limiting, pull-ups, base resistors, and dividers feeding high-impedance inputs are all fine with ±5%, because a 5% shift in current is invisible and a 5% shift in a divider ratio is well inside anything you'd care about.
- **When it matters:** precision dividers feeding an ADC you'll calibrate against, current-sense shunts, timing networks where τ has to be repeatable. Buy ±1% (E96 series) parts. **Never hand-select ±5% parts with a meter** — they drift with temperature and age, so you'd be selecting for today only.
- ⚠️ **Tolerances stack.** Two ±5% resistors in a divider can both be off in the directions that hurt. Worst-case ratio error is roughly the sum of the two, not 5%.

### A.3 Power rating — when a ¼ W resistor smokes

The rating is a **heat limit**, not a voltage or current limit. Current through resistance makes heat (P = I²R); the physical body can only shed so much before the value drifts, the coating scorches, and eventually the element opens.

- Common through-hole ratings: **1/8 W, 1/4 W (250 mW — the default), 1/2 W, 1 W, 2 W**. SMD: 0603 ≈ 1/10 W, 0805 ≈ 1/8 W, 1206 ≈ 1/4 W.
- **The check, every time:** compute P = I²R (or E²/R) and confirm it's under the rating. **Derate to ≥2×** — treat a ¼ W part as a 125 mW part, per Week 1's design loop step 3.
- Rearranged for design, the two limits on a ¼ W part:

  **I_max = √(P_rating / R)**  and  **V_max = √(P_rating · R)**

| R | V_max (¼ W) | I_max (¼ W) | with 2× derating |
|---|---|---|---|
| 10 Ω | 1.58 V | 158 mA | 1.12 V / 112 mA |
| 100 Ω | 5.0 V | 50 mA | 3.54 V / 35 mA |
| 220 Ω | 7.42 V | 33.7 mA | 5.24 V / 23.8 mA |
| 330 Ω | 9.08 V | 27.5 mA | 6.42 V / 19.5 mA |
| 1 kΩ | 15.8 V | 15.8 mA | 11.2 V / 11.2 mA |
| 10 kΩ | 50 V | 5.0 mA | 35.4 V / 3.5 mA |

- **Read that table as reassurance, then as a warning.** At logic voltages with kΩ-scale resistors you are nowhere near the limit — an LED resistor dissipates ~27 mW, about 10% of a ¼ W part. But drop into the tens of ohms and the margin evaporates fast.
- **The lab proved this.** The "stiff" divider (10 Ω / 20 Ω, same 1:2 ratio) burned **278 mW and 556 mW** — both past a ¼ W part, from a circuit whose whole job was producing 3.3 V at no current. See §Lab-1 log.
- ⚠️ **A ¼ W resistor at exactly ¼ W is ~100 °C on its surface.** It won't fail, but it will burn a finger, drift in value, and cook whatever's next to it on the board. "Within rating" is not "fine."
- **CS anchor:** derating is the same instinct as not running a server at 100% CPU. The spec is the cliff, not the operating point.

---

## Chapter B — Capacitors and the RC Time Constant

### B.1 What a capacitor physically is

- Two conductive plates separated by an insulator (**dielectric**). Charge piles up on one plate and is repelled off the other, storing energy in the **electric field between them**. No charge ever crosses the dielectric.
- **Capacitance C = Q/V** — coulombs stored per volt applied. Unit: farad (F). Practical parts are **pF, nF, µF**; a 1 F cap is a supercapacitor, not an ordinary component.
- More plate area → more capacitance. Thinner dielectric → more capacitance (and lower voltage rating — the trade is direct).
- **Energy stored: E = ½CV².** Quadratic in voltage, which is why a charged high-voltage cap is genuinely dangerous even at modest capacitance.

### B.2 The defining relationship — i = C·(dv/dt)

This one line generates everything else in the chapter:

**i = C · dv/dt**

- **Current is proportional to the *rate of change* of voltage**, not to voltage. A capacitor with a constant voltage across it passes zero current, no matter how large that voltage is.
- Rearranged: **dv/dt = i/C** — to change a capacitor's voltage you must move charge, and moving charge takes time. **A capacitor's voltage cannot change instantaneously.** That is the whole reason RC curves exist.
- Contrast with a resistor: resistors have no memory (i depends only on v *right now*), capacitors do (v depends on the entire history of i). This is the first **stateful** component in the course.
- **CS anchor:** a resistor is a pure function; a capacitor is an accumulator. `v += (i/C) * dt` in a loop. It integrates current.

### B.3 The two limiting behaviors — the sentence to memorize

> **At the instant of a step change, a capacitor behaves like a short circuit. Long after (DC steady state), it behaves like an open circuit.**

- **At t = 0:** the cap's voltage is whatever it was a moment ago (can't jump), so it holds that node and lets current through freely — a short, from the circuit's point of view.
- **At t = ∞:** fully charged, dv/dt = 0, so i = 0 — an open.
- Everything between those two endpoints is the exponential curve. If you can state these two limits you can sketch any RC response without doing math, which is 90% of what the intuition is for.
- **Consequences you'll use constantly:** this is why decoupling caps supply the instantaneous current spike when an IC switches, why an RC filter passes fast edges and blocks DC, and why a reset pin held by an RC comes up delayed.

### B.4 τ = RC and the charging curve

**τ = R · C**, and the units genuinely work out: Ω · F = (V/A)·(C/V) = C/A = C/(C/s) = **seconds**.

Charging a capacitor through a resistor from a step source:

**V(t) = V_final · (1 − e^(−t/τ))**

| t | Fraction of final | On a 5 V rail |
|---|---|---|
| 1τ | **63.2%** | 3.16 V |
| 2τ | **86.5%** | 4.32 V |
| 3τ | **95.0%** | 4.75 V |
| 4τ | 98.2% | 4.91 V |
| 5τ | **99.3%** | 4.97 V |

- **Memorize 63 / 86 / 95 / 99.** These four numbers are permanent furniture. "5τ ≈ settled" is the engineering rule of thumb everywhere.
- The curve **never mathematically arrives** — it's asymptotic. It just gets inside anyone's measurement noise by 5τ.
- **Why 63.2% specifically?** At any instant the driving voltage is the *remaining* difference, so the charging current — and thus the rate of change — falls as the cap fills. Exponential decay of the *rate*, exponential approach of the *value*. 1 − 1/e is what one time constant of that process buys you.
- **The current is the mirror image:** I(t) = (V/R)·e^(−t/τ). Starts at its maximum V/R (the cap is a short) and decays to zero (the cap is an open). **Put the scope on the resistor, not just the cap** — the current curve is where §B.3's two limits become visible.

### B.5 Discharging

**V(t) = V_initial · e^(−t/τ)** — the same shape flipped.

| t | Fraction remaining |
|---|---|
| 1τ | 36.8% |
| 2τ | 13.5% |
| 3τ | 5.0% |
| 5τ | 0.7% |

- Note 63.2% + 36.8% = 100%. Same constant, complementary views.
- **The universal form** (AAC's version, which handles any start and end point):

  **Change = (Final − Start) · (1 − e^(−t/τ))**, then **Value(t) = Start + Change**

  Charging from 0 and discharging to 0 are just the two special cases.

### B.6 τ only depends on the product

- **R = 10 kΩ, C = 100 µF → τ = 1 s.** Slow enough to watch in Falstad (turn the sim speed down).
- **R = 20 kΩ, C = 50 µF → τ = 1 s.** Identical curve. Double one, halve the other, nothing changes.
- **R = 1 kΩ, C = 1 µF → τ = 1 ms.** The debounce/filter ballpark.
- **R = 10 kΩ, C = 100 nF → τ = 1 ms.** Same, with the parts you actually own.
- Same τ, wildly different *currents*: the 10 kΩ version peaks at 0.5 mA, the 1 kΩ version at 5 mA. τ sets the timing; R sets the current cost.

### B.7 Capacitors in series and parallel — backwards from resistors

- **Parallel: C_T = C₁ + C₂ + …** (more plate area → more capacitance)
- **Series: 1/C_T = 1/C₁ + 1/C₂ + …** (thicker effective dielectric)
- ⚠️ It's the **opposite** of the resistor rules, and it trips everyone. The physical reason (area vs. thickness) is the only reliable way to remember which is which.

### B.8 Where this actually shows up in embedded work — plan-note

- **Decoupling / bypass caps (100 nF ceramic at every IC power pin).** When a chip's internals switch, it demands current faster than the power traces can deliver it (trace inductance). The local cap supplies that burst. §B.3's "short at t=0" is exactly the mechanism. **This is the single most common capacitor in your future schematics.**
- **Bulk capacitance (10–100 µF electrolytic) at the board's power entry** — same job, slower timescale.
- **Button debounce:** a switch bounces for ~1–10 ms. An RC with τ ≈ 1 ms (10 k + 100 nF) plus a Schmitt input smooths it. (Software debounce does the same in the time domain — knowing both is the point.)
- **Reset delay:** an RC on a reset pin holds it low while the supply stabilizes.
- **ADC input settling:** the ADC's internal sample-and-hold cap must charge through your source impedance. That's an RC, and it's the direct reason a **high-value divider feeding an ADC needs sampling time** — the divider's output resistance (R1∥R2, from Lab 1) *is* the R in that τ. **Week 1's loaded-divider work and this chapter meet here.**
- **CS anchor:** τ is a settling-time budget. Same reasoning as "how long before I can trust this value" in any async system — you wait a fixed number of time constants the way you'd wait a fixed number of timeouts.

---

## Chapter C — Diodes and Forward Voltage

### C.1 The one-way valve

- A **PN junction**: p-type (holes) joined to n-type (electrons). The junction develops a depletion region that permits current in one direction and blocks it in the other.
- **Anode** (triangle) → **cathode** (bar). Conventional current flows **in the direction the triangle points**, into the bar. The bar is the "stop" side, and it matches the physical band printed on the part.
- Forward-biased (anode positive) → conducts. Reverse-biased → blocks, up to a limit.

### C.2 Forward voltage — the number that matters

A conducting diode drops a roughly fixed **V_f**, almost independent of current over normal operating ranges:

| Type | V_f | Notes |
|---|---|---|
| Silicon signal/rectifier | **0.7 V** | 0.6–0.8 depending on current |
| Schottky | **0.2–0.4 V** | fast, low loss, higher leakage |
| Germanium | 0.3 V | mostly historical |
| LED, red/yellow/green | **1.8–2.2 V** | color ≈ photon energy ≈ V_f |
| LED, blue/white | **3.0–3.4 V** | the 3.3 V rail problem — see §D.4 |

- **"Roughly fixed" is the useful lie.** The truth is the Shockley equation: **I = I_S(e^(V/nV_T) − 1)**, with V_T ≈ 26 mV at room temperature. Current is *exponential* in voltage.
- ⚠️ **The consequence, and it's the whole reason LEDs need resistors:** a few tens of millivolts of extra forward voltage multiplies the current several-fold. Drive a diode from a voltage source and tiny variations — part tolerance, temperature, supply ripple — produce enormous current swings. **You current-drive diodes, never voltage-drive them.** The series resistor is what converts a voltage source into an approximate current source.
- **Temperature:** V_f falls roughly **−2 mV/°C**. A hot LED draws *more* current at fixed supply, which makes it hotter. That positive feedback is why high-power LEDs need real current regulation, not just a resistor.
- **CS anchor:** the exponential I-V curve is an unstable open-loop control surface. The resistor is the negative feedback that makes it controllable — more current → more drop across R → less voltage left for the diode.

### C.3 Reverse behavior and ratings

- Reverse-biased, the diode blocks (leakage in the nA–µA range) until **breakdown**, at which point it conducts hard and usually dies. The spec is **PIV / V_R** (peak inverse voltage).
- **Zener diodes** are built to survive and operate *in* reverse breakdown at a specified voltage — that's how they make cheap references and clamps.
- The three ratings that matter when you buy one: **I_F (forward current), V_R (reverse voltage), V_F at your operating current.**

### C.4 The parts you'll actually meet

| Part | Role |
|---|---|
| **1N4148** | small-signal switching, 100 V / 200 mA, fast |
| **1N4001–1N4007** | 1 A rectifiers, 50 V → 1000 V |
| **1N5817 / SS14** | Schottky, low V_f, reverse-polarity and freewheel duty |
| **Zener (e.g. 1N4733, 5.1 V)** | reference / clamp |
| **LED** | a diode that emits; see Chapter D |

- **Two applications to file away now:** **reverse-polarity protection** (a series diode so a backwards battery does nothing — costs V_f) and the **flyback/freewheel diode** across an inductive load (relay, motor) to give collapsing-field current a path instead of a destructive voltage spike. The second one comes back in Week 9 and is not optional.

---

## Chapter D — LEDs and the Current-Limiting Resistor

### D.1 Why an LED can't be connected directly

Because of §C.2. An LED is a diode with an exponential I-V curve and no meaningful internal resistance. Put 3.3 V across a 2.0 V LED with nothing in series and the current is limited only by the LED's bulk resistance and the supply's ability — which is to say, it's limited by the failure of the LED.

**The resistor's job is to absorb the difference and set the current.** It converts "5 volts" into "10 milliamps."

### D.2 The formula

**R = (V_supply − V_f) / I_target**

The numerator is **the voltage the resistor itself sees** — not the supply. This is Week 1 §5.6's same-two-points rule, and getting it wrong is the #1 beginner error in the whole subject.

Then the design loop from Week 1 runs as usual: compute → round to a standard value (**round up** for current limiting: higher R = less current = safer) → recompute the actual current → power check.

### D.3 Worked — the same LED on two rails

**5 V rail, red LED (V_f = 2.0 V), target 10 mA:**
- R = (5 − 2.0)/0.010 = 300 Ω → standard **330 Ω**
- Actual I = 3.0/330 = **9.1 mA** ✓ (perceived brightness is roughly logarithmic; 9 vs 10 mA is invisible)
- P = I²R = (9.1 m)² × 330 = **27 mW** ≪ 250 mW ✓

**3.3 V rail, same red LED, target 10 mA:**
- R = (3.3 − 2.0)/0.010 = 130 Ω → standard **150 Ω**
- Actual I = 1.3/150 = **8.7 mA** ✓
- P = (8.7 m)² × 150 = **11 mW** ✓

### D.4 The headroom lesson — the part that isn't obvious

Take the **330 Ω** sized for 5 V and move it to a 3.3 V rail without changing it:

- At 5 V: resistor sees 3.0 V → **9.1 mA**
- At 3.3 V: resistor sees 1.3 V → **3.9 mA**

**The supply fell 34%, but the current fell 57%.** The LED's V_f is fixed and takes its cut first; the resistor only ever gets the *leftover*. A modest supply drop eats a large fraction of the headroom, and current scales with the headroom, not with the supply.

⚠️ **Push this to the failure case: blue or white LED (V_f ≈ 3.2 V) on a 3.3 V rail.** Headroom is 0.1 V. For 10 mA you'd need a 10 Ω resistor — and since V_f varies ±0.2 V part to part and drifts −2 mV/°C, the actual current could be anywhere from **zero to destructive**. The circuit is not designable. **Check V_f against your rail before choosing a color** — this is a real design step, not a formality. Fixes: drive it from 5 V, use a boost converter, or use a proper constant-current LED driver.

### D.5 The GPIO is a circuit component too — plan-note

- Typical MCU pin: **~20 mA absolute maximum**, less recommended, **plus a total-across-all-pins budget** (often 100–200 mA for the whole chip) and per-port limits. Check the datasheet's Absolute Maximum Ratings table.
- "It worked on the bench" with eight LEDs at 20 mA each is 160 mA through the chip's ground bond wire. Design at **5–10 mA per indicator LED**; modern LEDs are bright enough.
- ⚠️ **Absolute Maximum Ratings are destruction limits, not operating points.** The recommended operating conditions table is the one you design to. Confusing the two is how parts die slowly.
- When the load needs more than the pin can give — that's Chapter E.

---

## Chapter E — The Transistor as a Switch

### E.1 The NPN and its three regions

Three terminals: **base (B)**, **collector (C)**, **emitter (E)**. A small base current controls a much larger collector current.

| Region | Condition | Behavior | Use |
|---|---|---|---|
| **Cutoff** | V_BE < ~0.6 V | I_C ≈ 0, open switch | OFF |
| **Active** | V_BE ≈ 0.7, V_CE > V_CE(sat) | I_C = β·I_B, linear amplifier | analog — **avoid for switching** |
| **Saturation** | enough base drive | V_CE ≈ 0.1–0.3 V, closed switch | ON |

- **The base-emitter junction is a diode.** It drops ~0.7 V (0.7–0.9 V when saturated) and has the exponential I-V of §C.2. **This is why a base resistor is mandatory** — same reason as an LED. Connect a GPIO straight to a base and you've shorted the pin through a forward diode.
- **Symbol mnemonic:** the arrow is on the **emitter**. **NPN = Not Pointing iN** (arrow points out). PNP points in. The arrow always shows conventional current direction.

### E.2 Saturate, don't amplify

For switching you want the transistor to be a **bit**, not a float — hard off or hard on, never in between.

- **Power dissipated in the transistor: P = V_CE × I_C.**
  - Saturated: 0.2 V × 20 mA = **4 mW**. Nothing.
  - Half-on in the active region, say V_CE = 2.5 V at 10 mA: **25 mW**, and at higher currents it climbs fast. A half-on transistor is a heater.
- ⚠️ **Do not design at the datasheet β.** β varies 3× across parts of the same model number, shifts with temperature and with I_C, and is specified as a range (2N3904: 100–300). Designing at β = 200 leaves you balanced on the edge of the active region, where every drifting parameter pushes you out of saturation.
- **Instead: deliberately overdrive.** Use a **forced β of 10** — supply ten times more base current than the "minimum," i.e. **I_B = I_C / 10**. Guarantees hard saturation across all part variation, and the wasted base current is microamps-to-milliamps of nothing.

### E.3 Base resistor sizing — the design order

1. **Decide I_C** — what the load actually needs.
2. **I_B = I_C / 10** (forced β = 10, per §E.2).
3. **KVL around the base loop:** the GPIO drives the base resistor and the B-E diode in series.

   **R_B = (V_GPIO − V_BE) / I_B**, with V_BE ≈ 0.7 V

4. **Round R_B DOWN**, not up. ⚠️ Smaller R_B → more base current → deeper saturation.
5. **Size the collector-side resistor including V_CE(sat)** — small, but include it as a habit. **Round R_C UP** — this is just the LED rule from §D.2, unchanged.

⚠️ **The two resistors round in OPPOSITE directions**, and this is the step most often botched. Both round toward *safety*, but "safe" points different ways in the two loops:

| Resistor | Direction | Failure it avoids |
|---|---|---|
| **R_B** (base) | **DOWN** | too little base current → falls out of saturation → transistor becomes a heater |
| **R_C** (collector) | **UP** | too much current → cooked LED |

Smaller resistor always means more current. You want *more* in the base loop and *less* in the collector loop. **R_C is not a new rule — it is Lab 3's LED resistor with V_CE(sat) subtracted.** Only R_B is new, and only R_B rounds down.

**Worked — 3.3 V GPIO switching a red LED at 20 mA off a 5 V rail:**

- I_C = 20 mA → I_B = **2 mA**
- R_B = (3.3 − 0.7)/0.002 = 1300 Ω → **1.2 kΩ** (rounded down) → actual I_B = 2.6/1200 = **2.17 mA**
- R_C = (5 − V_f − V_CE(sat))/I_C = (5 − 2.0 − 0.2)/0.020 = 140 Ω → **150 Ω** → actual I_C = 2.8/150 = **18.7 mA**
- **Power checks:** R_B = 5.6 mW ✓ · R_C = 52 mW ✓ · transistor = 0.2 × 18.7 m = **3.7 mW** ✓

**The point of the whole exercise:** the GPIO supplies **2.17 mA** and the LED gets **18.7 mA**. An 8.6× gain — and for a relay or motor at 500 mA the ratio is the difference between "possible" and "destroyed pin." *That current ratio is the entire reason the transistor exists.*

**The framing that makes the whole procedure make sense:** a transistor switch is **two separate loops that share the emitter.** A small base loop the GPIO can afford to drive, and a big collector loop that does the work. Each gets its own KVL, its own resistor, its own calculation. Steps 1–4 are the base loop; step 5 is the collector loop.

Walk the collector loop as a voltage staircase and it stops being abstract — start at the rail and spend it down to ground:

```
5.0 V  rail
 ↓ −2.8   R_C          ← the leftover; you choose this via Ohm's law
2.2 V
 ↓ −2.0   LED V_f      ← fixed by physics
0.2 V  ← collector node
 ↓ −0.2   V_CE(sat)    ← fixed by the part
0.0 V  emitter / ground        2.8 + 2.0 + 0.2 = 5.0 ✓ KVL closes
```

Two of the three drops were decided before you started. **The resistor gets what's left** — same structure as the LED headroom lesson in §D.4.

⚠️ **Read the conditions column, not just the value.** Every V_BE(sat), V_CE(sat), and β figure on a datasheet comes with an I_C and I_B attached, and the number is only valid near that operating point. A 2N2222-type sheet lists V_BE(sat) = 0.75 V **at I_C = 10 mA, I_B = 1 mA** — if that matches your design, use it instead of the generic 0.7 V.
- **V_BE(sat) > V_BE(active)** for real: saturation forward-biases the B-C junction too, and larger base current produces ohmic drops in the internal base/emitter resistance.
- But the high figures (0.85–1.2 V) are quoted at **high current** — 2N2222 hits ~1.2 V at I_C = 150 mA / I_B = 15 mA. At indicator-LED currents you're much closer to 0.7 V.
- **Practical rule:** 0.7 V at indicator currents; 0.9–1.0 V when I_B reaches tens of mA (relays, motors).
- ⚠️ Don't mix parts. Advice written for a 2N3904 does not transfer to a 2N2222. When sources disagree, **the datasheet for the part you're actually using wins.**

### E.4 Two circuit details that aren't optional

- **Base pull-down (10 kΩ, base to ground).** During MCU reset and before GPIO configuration, the pin is a **floating input** — it doesn't drive low, it drives nothing, and a floating base picks up noise and can partially turn the transistor on. The pull-down defines the off state. ⚠️ **Every MCU-driven switch needs this.**
  - **Placement:** from the **base node to ground** — the node where R_B meets the base, i.e. in parallel with the B-E junction. Not on the GPIO side of R_B.
  - **It solves a state the circuit passes *through*, not one it sits in.** MCU pins default to high-impedance inputs at power-up. For those milliseconds the base is connected to something driving nothing; stray capacitance and noise drift it up, and past ~0.6 V the transistor starts conducting. Relay chatter or a motor twitch during the exact window nobody is in control.
  - **It makes the base a three-branch node — Lab 1's divider node again.** With the GPIO high the base sits at ~0.7 V, so a 10 kΩ pull-down draws 0.7/10 k = **70 µA** to ground. KCL: current in through R_B = current into the base + current down the pull-down. Costs ~6 % of base drive, irrelevant when overdriven 10×.
  - **Why 10 kΩ:** 1 kΩ holds harder against noise but steals 0.7 mA (over half the base current); 100 kΩ steals nothing but holds weakly. 10 kΩ is the standard compromise.
  - **Grounds:** all ground symbols are one net (§G.4's net-label rule). Drop a fresh ground symbol under the pull-down rather than routing a wire back — that is exactly why schematics scatter ground symbols instead of crisscrossing the sheet.
- **Low-side switching is the default for NPN.** Load goes between the supply and the **collector**; the **emitter goes to ground**. This works because V_BE is measured against the emitter, which is at a known 0 V.
  - ⚠️ Put the load *below the emitter* instead and it breaks: the emitter now floats up to the load voltage, so the base would need to be ~0.7 V above *that* — often above your supply rail. Worth building the broken version once in Falstad and watching the base drive collapse.
  - High-side switching needs a PNP, a P-channel MOSFET, or a gate driver. Week 9.

### E.5 The MOSFET — voltage-controlled instead of current-controlled

Terminals: **gate (G)**, **drain (D)**, **source (S)**. N-channel is the low-side workhorse.

- **The gate draws essentially no steady current — it's a capacitor.** No base resistor math, no continuous drive cost. But it *does* take a current pulse to charge that gate capacitance every switching transition, which is why gate charge matters at high frequency.
- **V_GS(th) — the threshold.** Below it, off. But threshold is where the FET *starts* conducting, not where it's fully on.
- ⚠️ **The single most common beginner MOSFET failure: using a standard MOSFET on a logic-level gate drive.** An IRF540N specifies its R_DS(on) at **V_GS = 10 V**. Drive it from a 3.3 V or 5 V GPIO and it's barely on — high resistance, large I²R loss, and it gets hot enough to fail while the datasheet says it can handle 30 A. **Look for "logic level" and check that R_DS(on) is specified at 2.5 V or 4.5 V** (IRLZ44N, IRL540N — note the **L**).
- **R_DS(on)** is the on-state resistance; conduction loss is **P = I²·R_DS(on)**. A good logic-level part is in the milliohms, which is why MOSFETs beat BJTs at high current — no fixed 0.2 V drop, just a small resistance.
- **Two resistors you still need:**
  - **Gate resistor (~100 Ω)** — *not* for current limiting. It damps the LC ringing between gate capacitance and lead inductance during transitions, and limits the peak current the driving pin sees while charging the gate.
  - **Gate pull-down (10 k–100 k)** — mandatory for the same floating-pin reason as §E.4, and more urgent here: a gate capacitance with nowhere to discharge *holds its charge* and keeps the FET on after the drive goes away.

### E.6 Which one — plan-note

| | **BJT (NPN)** | **MOSFET (N-channel logic level)** |
|---|---|---|
| Drive | continuous base current | ~zero steady current, gate charge per switch |
| On-state loss | fixed V_CE(sat) ≈ 0.2 V → P = 0.2·I | P = I²·R_DS(on) |
| Best at | small loads, < ~100 mA, cheap and forgiving | higher current, low loss, battery-powered |
| Watch out for | β variation, base drive budget | V_GS(th) vs. your rail; floating gates |
| Starter parts | 2N3904 (200 mA), BC547, 2N2222 (800 mA) | 2N7000 (200 mA), IRLZ44N (high current) |

**Rule of thumb:** LED or small load driven by a GPIO → NPN is fine and simpler. Motor, relay, LED strip, anything over ~100 mA or on a battery → logic-level MOSFET.

---

## Chapter F — What a Voltage Regulator Does

### F.1 The problem, stated from the lab

**Lab 1 proved a divider cannot power anything.** The full argument, since it's the conceptual bridge into this chapter:

1. **The output voltage is a property of the divider *plus its load*.** 3.33 V unloaded, 2.00 V with a 1 kΩ load. Same parts, 40% error, purely because current was drawn.
2. **Stiffness costs watts.** Output resistance is R1∥R2, so to hold 3.3 V at 20 mA within 1% you'd need ~1.7 Ω — a divider drawing **667 mA and burning 3.4 W to deliver 66 mW**. About **2% efficient**, and flowing whether the load is connected or not.
3. **Real loads aren't a fixed resistance.** An MCU asleep vs. transmitting differs by 10×. There is no divider value that's correct for both, so the rail *wanders* as the load does its job — brownout resets and garbage ADC readings.
4. **Nothing in a divider can notice or correct.** It's **open loop**: two resistors obeying Ohm's Law with no feedback path.

### F.2 Linear regulators — 7805 and LDOs

- **Mechanism: closed loop.** An internal voltage reference, an error amplifier, and a pass transistor. The regulator continuously measures its own output, compares it to the reference, and adjusts the pass element to correct. **That feedback is the entire difference from a divider** — output resistance in the milliohms instead of hundreds of ohms.
- **It burns the difference as heat: P = (V_in − V_out) × I_load.** Efficiency ≈ **V_out / V_in**.
  - 5 V → 3.3 V at 100 mA: 170 mW wasted, **66%** efficient. Fine.
  - 12 V → 5 V at 500 mA: **3.5 W** wasted. Needs a real heatsink.
  - 48 V → 5 V: **10%** efficient. Absurd — see §Hooks, ebike.
- **Dropout voltage** — the minimum V_in − V_out for regulation to hold:
  - **7805:** ~2 V dropout, so V_in ≥ 7 V. Classic, robust, thirsty.
  - **LDO (low dropout):** 0.1–0.5 V. **AMS1117-3.3** (~1.1 V, everywhere on dev boards), **MCP1700** (~0.2 V, 1.6 µA quiescent — the battery-friendly choice).
- ⚠️ **Quiescent current (I_Q)** is what the regulator burns doing nothing. Irrelevant on USB power, decisive on a coin cell — the same Week 1 lesson as pull-up sizing.
- ⚠️ **Regulators need their input and output capacitors**, and many LDOs are picky about the output cap's type and ESR. This is a datasheet requirement, not a suggestion; the wrong cap makes the feedback loop oscillate.

### F.3 Switching regulators — the buck converter

- **Mechanism:** rapidly switch the input on and off into an inductor + capacitor, and let the LC average it. Energy is *stored and released* rather than *burned*, so the loss is only in the switch resistance and magnetics.
- **85–95% efficient**, and — the important structural difference — efficiency **doesn't collapse as the input/output ratio grows**. A buck stepping 48 V to 5 V is still ~90%.
- Cost: more parts (inductor, catch diode or synchronous FET, careful capacitor selection), switching noise / EMI, and layout that actually matters. Ripple at the switching frequency rides on the output.
- **Boost** (step up) and **buck-boost** exist too; same family.

### F.4 Choosing — plan-note

| Situation | Choice |
|---|---|
| Small current, small V_in−V_out, quiet output needed (analog, RF, ADC reference) | **LDO** |
| 5 V → 3.3 V at tens of mA | **LDO** — 66% is acceptable at these powers |
| Big current, or big V_in−V_out | **Buck** — anything else needs a heatsink |
| Battery-powered anything | **Buck**, or an LDO with µA-class I_Q |
| A reference voltage into a high-impedance input | **A divider is correct here** — see below |

### F.5 What dividers *are* for

Not "dividers are bad." They're everywhere — just never as a source of power. The legitimate use is **measuring and referencing**, where the load draws essentially no current:

- **Scaling a voltage into an ADC input** (µA or less). *This is exactly how you'd read the 48 V ebike pack on a 3.3 V ADC — divide ~15:1, high-ohm, and mind Week 1 §3's safety rules while probing it.*
- **Setting a bias voltage** into an op-amp or comparator input.
- **Pull-ups and pull-downs** — a divider where one leg is a switch.

**The unifying rule: a divider is fine when the load resistance is enormous compared to R1∥R2, and useless when it isn't.** Powering means the load is small. Measuring means it's huge.

---

## Chapter G — How to Read a Schematic

A schematic is a **graph**, not a picture. It says nothing about physical placement — only about what connects to what. Learning to read one is learning to see the netlist through the drawing.

### G.1 Symbols worth recognizing instantly

| Symbol | Part | Notes |
|---|---|---|
| zigzag (US) / rectangle (IEC) | resistor | both are current; know both |
| two parallel lines | capacitor, non-polarized | ceramic, film |
| one straight + one curved line, or a `+` | **polarized** capacitor | electrolytic/tantalum — ⚠️ backwards = vents |
| triangle into a bar | diode | current flows toward the bar |
| diode + two outward arrows | LED | arrows out = emitting |
| coil / loops | inductor | |
| circle with arrow on emitter | BJT | **arrow out = NPN**, in = PNP |
| three-terminal with gate bar | MOSFET | body diode is often drawn |
| triangle to a line, or three descending bars | ground | |

### G.2 Junction dots — the highest-stakes convention

- **Wires that cross *without* a dot are NOT connected.** They're passing over each other on different nets.
- **A dot means connected.** One net.
- ⚠️ **Modern practice avoids 4-way junctions entirely** — a dot that gets lost in a photocopy or a low-DPI render turns one net into two, and it's a nightmare to debug. Instead, two staggered **T-junctions** are drawn. If you see a 4-way crossing *with* a dot, be suspicious and check the netlist.
- Some old schematics use a "hop" (little semicircle) to show non-connection. Recognize it, don't draw it.

### G.3 Power rails and ground

- Convention: **power at the top, ground at the bottom, signal flow left to right.** Follow it in your own drawings; violating it makes a schematic unreadable even when it's electrically correct.
- Rails are drawn as short stubs labeled **VCC / VDD / +5V / +3V3** rather than long wires everywhere. Every stub with the same name is the same net.
- Multiple ground symbols: **AGND** (analog), **DGND** (digital), **earth**. Different symbols mean deliberately different nets, joined at exactly one point.

### G.4 Net labels — the feature that makes real schematics readable

- A **net label** is a name attached to a wire. **Two wires with the same label are electrically connected even with no line drawn between them.**
- This is how a 200-component board fits on three readable sheets instead of one spaghetti diagram.
- ⚠️ **Typos in net labels create silent bugs** — `SPI_MOSI` and `SPI_MOS1` are two different nets that look identical at a glance. This is exactly a variable-name typo, and the ERC (electrical rule check) that catches single-node nets is your compiler warning.
- **CS anchor:** drawn wires are explicit references; net labels are named variables in a shared scope. The schematic is source code; the PCB is the compiled binary.

### G.5 Designators and values

- **R**esistor · **C**apacitor · **L** inductor · **D**iode · **Q** transistor · **U** integrated circuit · **J** connector · **SW** switch · **Y/X** crystal · **TP** test point.
- Numbered R1, R2, C1… and the value is printed separately (330 Ω, 100 nF). The designator is the identity; the value is the parameter. The BOM joins them.

### G.6 Reading discipline — the order to do it in

1. **Find the power rails and ground first.** Everything else is interpreted relative to them.
2. **Find the ICs** and identify what each one is. They're the nouns; everything else is support.
3. **Trace one signal path at a time**, left to right, and ignore the rest of the sheet while you do.
4. **Recognize the clichés.** 100 nF next to a power pin is a decoupling cap and carries no information — skip it. A resistor pair from a rail to ground into an ADC pin is a divider. A diode across a relay coil is a flyback. Learning the idioms is most of the fluency.
5. ⚠️ **Real schematics are never drawn for your convenience.** Vendor reference designs and datasheet application circuits are laid out for the drafter, not the reader. Re-drawing a confusing section by hand — the Week 1 §7.3 normalization habit — is the tool.

---

## Week 2 map — everything in one place

*(One consolidated block, per plan: core idea → the one thing never to forget.)*

**A — Resistors for real.** Color code is digits + multiplier + tolerance; ±5% is a contract, not a defect; the wattage rating is a **heat** limit. Never forget: **compute P = I²R and derate 2×**, and remember that the resistors small enough to make a divider stiff are the ones that smoke.

**B — Capacitors & RC.** i = C·dv/dt, so voltage cannot change instantly; τ = RC; charging hits **63 / 86 / 95 / 99%** at 1/2/3/5τ. Never forget: **a capacitor is a short at the instant of a step and an open long after** — that one sentence explains decoupling, filtering, reset delays, and ADC settling.

**C — Diodes.** One-way valve with a roughly fixed V_f (Si 0.7, Schottky 0.3, LED 1.8–3.4), but the underlying I-V is **exponential**. Never forget: **current-drive diodes, never voltage-drive them** — the series resistor is the negative feedback that makes them controllable.

**D — LEDs.** R = (V_s − V_f)/I_f, where the numerator is what **the resistor** sees. Never forget: **V_f takes its cut first and the resistor gets the leftover**, so a small supply drop is a large current drop — and a 3.2 V blue LED on a 3.3 V rail is not a designable circuit.

**E — Transistor as a switch.** Two loops sharing the emitter. Cutoff or saturation, never active. **I_B = I_C/10** (forced β), R_B = (V_GPIO − V_BE)/I_B rounded **down**, R_C rounded **up**. Never forget: **don't design at β**, **the two resistors round opposite ways**, always add the base/gate pull-down, low-side is the default — and the whole point is the current ratio between what the pin supplies and what the load draws.

**F — Regulators.** Linear/LDO burns (V_in − V_out)·I as heat with efficiency V_out/V_in; buck switches into an inductor at 85–95% and doesn't care about the ratio. Never forget: **a regulator is closed loop and a divider is open loop** — that feedback is the entire difference, and it's why dividers make references, not supplies.

**G — Schematics.** A graph, not a picture. Never forget: **no dot = no connection**, same net label = same wire even with no line drawn, and read power rails first.

---

## The practical playbook — Week 2 recipes

*(Continuing Week 1's playbook. Same four-step design loop every time: identify constraint → R = E/I with the **right** E → power check → round to standard and re-verify.)*

### Recipe 4 — sizing an RC for a target time

1. **Decide the time you want**, then divide: **τ = t_target / 5** if you need it settled, or τ = t directly if you're aiming at the 63% point (comparator thresholds, timing).
2. **Pick R from the current budget, then solve for C.** R sets how much current the network draws; C follows from C = τ/R.
3. **Round C to a standard value** (100 nF, 1 µF, 10 µF, 100 µF — the ones you own), then recompute the actual τ.
4. ⚠️ **Check the tolerance.** Ceramic caps are commonly ±10–20% and **X7R/Y5V lose capacitance with applied DC voltage and temperature** — a "1 µF" X7R at rated voltage can be half that. For anything where τ must be repeatable, use C0G/NP0 (tight, stable, but only available in small values) or design so ±20% doesn't matter.

### Recipe 5 — the NPN low-side switch (the full checklist)

```
Given: V_GPIO, V_supply, load (I_C and its own voltage drop)

1. I_B  = I_C / 10                              forced β, not datasheet β
2. R_B  = (V_GPIO − 0.7) / I_B                  → round DOWN to standard
3. R_C  = (V_supply − V_load − 0.2) / I_C       → round UP to standard
                                                (opposite of step 2 — see E.3)
4. Pull-down 10 kΩ base→GND                     defines OFF while pin floats
5. Power: R_B, R_C via I²R · transistor via V_CE(sat)·I_C
6. If load is inductive → flyback diode across it, cathode to +V
```

### Recipe 6 — choosing the power path

1. **What's V_in, what's V_out, what's I_max?**
2. **P_wasted = (V_in − V_out) × I_max** if linear. Under ~1 W and you can use a linear regulator without a heatsink; over that, buck.
3. **Check dropout:** V_in(min) must exceed V_out + dropout **at the lowest point of your input's range** — a "12 V" wall wart sagging to 9 V under load still clears a 7805, a 3.7 V LiPo at 3.4 V does *not* clear an AMS1117 for 3.3 V out.
4. **Check quiescent current against the power budget** if it's battery-powered.
5. **Add the datasheet's required input/output caps.** Non-negotiable.

### The dispatch table — Week 2 additions

| you know | you want | reach for |
|---|---|---|
| R and C | how long until settled | τ = RC, then ~5τ |
| τ and elapsed time | fraction charged | 1 − e^(−t/τ) (63/86/95/99 at 1/2/3/5τ) |
| supply, LED color, target brightness | the resistor | R = (V_s − V_f)/I_f, round **up** |
| GPIO voltage, load current | base resistor | I_B = I_C/10 → R_B = (V_GPIO − 0.7)/I_B, round **down** |
| a load over ~100 mA, or a battery | which switch | logic-level MOSFET, check V_GS(th) |
| V_in, V_out, I | linear or switching | P = (V_in−V_out)·I — over ~1 W → buck |
| a resistor about to be bought | will it survive | P = I²R, rating ≥ 2× |
| a circuit that needs a stable rail under varying load | anything | **a regulator, never a divider** |

---

## Formula sheet

```
RESISTOR RATINGS
P = I²R = E²/R = I·E            derate: buy ≥ 2× the computed dissipation
I_max = √(P_rating / R)         V_max = √(P_rating · R)
¼ W quick limits:  1 kΩ → 15.8 V / 15.8 mA  ·  100 Ω → 5 V / 50 mA  ·  10 Ω → 1.58 V / 158 mA
E12 decade:  10 12 15 18 22 27 33 39 47 56 68 82     (±5% on 330 Ω = 313.5–346.5 Ω)

CAPACITORS
C = Q/V   [farad = coulomb/volt]        E_stored = ½CV²
i = C·dv/dt        ← the defining relation; voltage cannot change instantly
t = 0:  cap ≈ SHORT        t = ∞:  cap ≈ OPEN        ← memorize this line
Parallel: C_T = C₁ + C₂ + …            Series: 1/C_T = 1/C₁ + 1/C₂ + …   (backwards from resistors!)

RC TIME CONSTANT
τ = R·C     [Ω·F = seconds]
Charging:     V(t) = V_f·(1 − e^(−t/τ))       I(t) = (V/R)·e^(−t/τ)
Discharging:  V(t) = V_i·e^(−t/τ)
Universal:    Change = (Final − Start)(1 − e^(−t/τ));  Value = Start + Change
        1τ = 63.2%   2τ = 86.5%   3τ = 95.0%   4τ = 98.2%   5τ = 99.3% ("settled")
        remaining:  1τ = 36.8%   2τ = 13.5%   3τ = 5.0%   5τ = 0.7%
Same τ, different cost: 10k+100µF and 1k+1000µF both = 1 s, but peak current differs 10×

DIODES
V_f ≈ 0.7 Si · 0.3 Schottky · 1.8–2.2 LED red/yel/grn · 3.0–3.4 LED blue/white
I = I_S(e^(V/nV_T) − 1),  V_T ≈ 26 mV     ← exponential: NEVER voltage-drive a diode
V_f drifts ≈ −2 mV/°C                      ratings: I_F, V_R (PIV), V_F @ current

LED
R = (V_supply − V_f) / I_target            numerator = what the RESISTOR sees
        5 V, red 2.0 V, 10 mA → 300 → 330 Ω → 9.1 mA, 27 mW ✓
        3.3 V, red 2.0 V, 10 mA → 130 → 150 Ω → 8.7 mA ✓
        ⚠ 3.3 V + blue 3.2 V → 0.1 V headroom → not designable
GPIO: ~20 mA absolute max per pin, plus a total-across-all-pins budget — design at 5–10 mA

BJT SWITCH (NPN, low side)
V_BE ≈ 0.7 V (B-E is a diode) · V_CE(sat) ≈ 0.1–0.3 V · cutoff / SATURATION only, never active
I_B = I_C / 10                             forced β — do NOT design at datasheet β
R_B = (V_GPIO − V_BE) / I_B                → round DOWN (more base drive = safe)
R_C = (V_supply − V_load − V_CE(sat)) / I_C → round UP (less LED current = safe)
      ⚠ OPPOSITE directions. R_C is just the LED rule; only R_B is new.
V_BE: 0.7 nominal · check the datasheet's CONDITIONS column (I_C, I_B) for a better figure
      0.9–1.0 V once I_B reaches tens of mA
P_transistor = V_CE × I_C                  saturated ≈ mW · half-on = heater
Always: 10 kΩ base→GND pull-down · inductive load → flyback diode

MOSFET SWITCH (N-channel, low side)
Gate = capacitor: ~0 steady current, but gate charge per transition
V_GS(th) = where it STARTS conducting, not where it's fully on
⚠ "logic level" = R_DS(on) specified at V_GS = 2.5 V or 4.5 V (IRLZ44N), NOT 10 V (IRF540N)
P_conduction = I² · R_DS(on)
Always: 100 Ω gate series (damping) · 10 k–100 k gate→GND pull-down (mandatory)

REGULATORS
Linear:  P_wasted = (V_in − V_out)·I_load        efficiency ≈ V_out/V_in
         dropout: 7805 ≈ 2 V · AMS1117 ≈ 1.1 V · MCP1700 ≈ 0.2 V
         5→3.3 V = 66% · 12→5 V = 42% · 48→5 V = 10%
Buck:    85–95%, efficiency ~independent of ratio; costs inductor, noise, layout care
Closed loop (reference + error amp + feedback) — THIS is what a divider lacks
Divider output resistance = R1∥R2 → dividers make REFERENCES, not supplies

SCHEMATIC
no dot = NOT connected · dot = connected · avoid 4-way junctions, use staggered T's
same net label = same net, even with no line drawn
power top / ground bottom / signal left→right
R C L D Q U J SW Y/X TP    (Q = transistor, U = IC)
Absolute Maximum Ratings = destruction limits; design to Recommended Operating Conditions
```

---

## Week 2 self-check — worked

1. **Decode brown-black-orange-gold.** 1, 0, ×1k → **10 kΩ ±5%** (9.5–10.5 kΩ conforming).
2. **A 100 Ω resistor across a 12 V rail — does a ¼ W part survive?** I = 12/100 = 120 mA; P = I²R = 0.0144 × 100 = **1.44 W**. Nearly **6× over rating** — it smokes. V_max for ¼ W at 100 Ω is only 5 V. ✓ caught by the check.
3. **τ for 4.7 kΩ + 10 µF?** τ = 4700 × 10⁻⁵ = **47 ms**. Settled (5τ) in ~235 ms.
4. **Same network, charging from a 3.3 V rail — voltage at 94 ms?** 94 ms = 2τ → 86.5% → **2.85 V**.
5. **How long to reach 3.0 V?** 3.0/3.3 = 90.9%, which is between 2τ (86.5%) and 3τ (95%). Exactly: t = −τ·ln(1 − 0.909) = −0.047 × ln(0.091) = 0.047 × 2.40 = **113 ms**.
6. **Why does a 1 µF cap in series with a 1 µF cap give 0.5 µF, when two 1 kΩ resistors in series give 2 kΩ?** Because series capacitors stack their dielectrics — effectively one capacitor with twice the plate separation, and capacitance falls with separation. The rules are inverted because the *geometry* is inverted. (Parallel = more area = more C.)
7. **Pick the resistor: 5 V rail, green LED V_f = 2.1 V, target 12 mA.** R = (5 − 2.1)/0.012 = 241.7 Ω → **270 Ω** (round up) → actual I = 2.9/270 = **10.7 mA** ✓. P = (10.7 m)² × 270 = **31 mW** ≪ 250 mW ✓.
8. **Same LED and resistor moved to 3.3 V — predict the current before computing.** Headroom drops from 2.9 V to 1.2 V, so current should fall by more than the supply did. I = 1.2/270 = **4.4 mA** — the supply fell 34%, the current fell **59%**. ✓ §D.4's lesson, in numbers.
9. **A 5 V GPIO switching a 12 V relay coil that draws 80 mA. Size R_B.** I_B = 80/10 = **8 mA**. R_B = (5 − 0.7)/0.008 = 537.5 Ω → **470 Ω** (round down) → actual I_B = 4.3/470 = **9.15 mA**, forced β = 8.7 ✓. Plus: **10 kΩ base pull-down**, and ⚠️ **a flyback diode across the coil** — an inductive load without one destroys the transistor on turn-off.
10. **You have an IRF540N and a 3.3 V GPIO. Why won't this work, and what fails first?** The IRF540N is a standard (non-logic-level) MOSFET whose R_DS(on) of 44 mΩ is specified at V_GS = 10 V. At V_GS = 3.3 V it's barely above threshold, sitting in the linear region with an on-resistance orders of magnitude higher. **What fails first is thermal:** P = I²·R_DS(on) with a huge R_DS(on) → the FET heats → and since it never turns fully on, there's no operating point where that resolves. Fix: a logic-level part (IRLZ44N), or a gate driver to supply 10 V.
11. **Why does a divider sag but a regulator doesn't, in one sentence each?** The divider's output is set by a resistance ratio, and the load changes that ratio by paralleling the bottom leg — with no mechanism to notice. The regulator continuously measures its own output against an internal reference and drives a pass element to correct the difference, so its output resistance is milliohms instead of R1∥R2.
12. **Two wires cross on a schematic with no dot. Connected?** **No.** And if it's a 4-way crossing *with* a dot, treat it as suspect and verify against the netlist — that's precisely the case modern practice avoids by using staggered T-junctions.

---

## Falstad labs — Week 2

### Lab 1 — Voltage divider + load ✅ COMPLETE (~3 h)

- [x] Design 3.3 V from 5 V: derive the ratio from Ohm's law rather than looking up the formula
- [x] Choose absolute values; compute standing current and P per resistor; check against ¼ W
- [x] Build vertically (rail top, ground bottom) and verify unloaded V_out
- [x] Predict the loaded value by hand **before** attaching the 1 kΩ
- [x] Verify the sag; verify KCL at the output node
- [x] Compute R1∥R2 and relate it to the load
- [x] SPST switch in series with the load to toggle the sag live
- [ ] *Deferred:* sweep the load (100 k → 100 Ω, 8 points) and plot V_out vs. R_load; find the knee and compare to R1∥R2
- [ ] *Deferred:* rebuild at 10 Ω / 20 Ω and confirm both the reduced sag and the >¼ W dissipation

### Lab 2 — RC charging curve ⬜ TOMORROW

- [x] Pick R and C so τ is watchable (10 k + 100 µF → τ = 1 s); slow the Falstad sim speed down
- [x] **Predict first:** write down the expected voltage at 1τ, 2τ, 3τ from the exponential
- [x] Scope the capacitor, run, and check the three points against the prediction
- [x] **Scope the resistor too** — confirm the current is the mirror image, starting at V/R and decaying
- [ ] Verify §B.3 directly: at t=0 the cap acts as a short (full current, ~0 V across it); at t=∞ as an open (0 current, full V across it)
- [ ] **Double R and halve C.** Predict, then confirm the curve is unchanged — τ is the only thing that matters
- [ ] Note the peak currents in both versions and record how they differ even though τ didn't
- [x] Add a switch to discharge through the same resistor; confirm 36.8% / 13.5% / 5.0%

### Lab 3 — LED + resistor at 5 V and 3.3 V ⬜ TOMORROW

- [x] Size and build both: 5 V rail (330 Ω) and 3.3 V rail (150 Ω); predict currents first
- [x] **Take the 5 V-sized 330 Ω and move it to the 3.3 V rail.** Predict the current *before* running; confirm the drop is much larger than the supply's drop (§D.4)
- [x] Swap to a blue/white LED (V_f ≈ 3.2 V) on the 3.3 V rail; try to design a resistor and document why you can't
- [ ] Compute the resistor's dissipation at 10 mA, then at 200 mA, and note where the ¼ W line falls
- [ ] Sweep V_f ±0.2 V (part tolerance) at fixed R on both rails; record how much the current moves in each case — this quantifies "headroom buys you insensitivity"

### Lab 4 — NPN switching an LED from a "GPIO" ✅ CORE COMPLETE

- [x] Design in order: I_C → I_B = I_C/10 → R_B by KVL → R_C including V_CE(sat). Write the numbers down before building.
- [x] Build it: 3.3 V source as the "GPIO", NPN low-side, LED + R_C on the 5 V rail
- [x] **Compare the GPIO's current to the LED's current.** That ratio is the reason the transistor exists — record it.
- [x] Verify saturation: V_CE collapses from ~5 V (off) to a few hundred mV (on)
- [x] Compute transistor dissipation P = V_CE × I_C
- [x] Add the 10 kΩ base pull-down; understand placement (base node → ground) and the 70 µA cost
- [ ] Add a slider to R_B (right-click → slider). Sweep upward: watch the LED dim and V_CE rise.
- [ ] At a mid-sweep point compute **P = V_CE × I_C** and compare it to the saturated value — the half-on heater, in numbers
- [ ] Remove the drive entirely to simulate a floating pin, observe, then confirm the pull-down fixes it
- [ ] **Deliberately break it:** move the LED below the emitter (high-side attempt) and watch the base drive collapse. Document why low-side is the NPN default.
- [ ] Stretch: rebuild with a logic-level MOSFET and compare gate current to base current

### Standing habits

- [ ] Export every circuit (**File → Export as Text** for git-diffable, **Export as Link** for quick sharing) into the repo next to the notes
- [ ] Every lab gets a **predicted / measured / delta** table — that table is the deliverable
- [ ] ⚠️ **Pick values that can't collide.** See the Lab 1 log — duplicated numbers across different quantities cost real debugging time. Deliberately choosing ugly, distinct values is a technique, not a crutch.

---

## Lab log — Divider Lab (Part 1)

**Time:** ~3 hours. **Status:** core objective complete; three follow-ups deferred to Part 2.

**Design:** R1 = 1 kΩ (top), R2 = 2 kΩ (bottom), 5 V rail.

| Quantity | Predicted | Measured | Δ |
|---|---|---|---|
| V_out unloaded | 3.33 V | 3.33 V | ✓ |
| R2 ∥ R_load (1 kΩ) | 667 Ω | — | ✓ |
| V_out loaded | 2.00 V | 2.00 V | ✓ |
| I through R1 | 3.0 mA | 3.0 mA | ✓ |
| I through R2 | 1.0 mA | 1.0 mA | ✓ |
| I through load | 2.0 mA | 2.0 mA | ✓ |
| Output resistance R1∥R2 | 667 Ω | — | ✓ |

- **KCL verified at the output node:** 3.0 mA in = 1.0 + 2.0 mA out. First time deriving Kirchhoff's current law from my own measurement rather than reading it.
- **Result that matters:** designed for 3.33 V, got 2.00 V under a 1 kΩ load — a **40% error** caused purely by drawing current. Output resistance (667 Ω) is comparable to the load (1 kΩ), which is exactly the condition for large sag. The general rule: **a source holds its voltage only when its output resistance is ≪ the load, roughly 10× or more.**

**Mistakes logged (worth more than the correct answers):**

1. ⚠️ **Stopped one step early on the reciprocal parallel formula.** Computed 1/2 + 1/1 = 1.5 and labeled it **1.5 kΩ**. The reciprocal form gives **1/R_p**, not R_p — the answer needed inverting: 1/1.5 = 0.667 kΩ. **The units were the tell:** 1/2 + 1/1 has units of 1/kΩ = **millisiemens**, i.e. conductance, not resistance. Resistances don't add as reciprocals; **conductances do** (Week 1 §5.4). Then compounded it by computing R_total = 1 + 1.5 = 2.5 kΩ — adding a resistance to a conductance, two different physical quantities.
   - **How it was caught:** computed total current two ways and got **3 mA and 2 mA**. The contradiction, not the arithmetic, is what surfaced the bug. *Noticing that two routes to the same quantity disagree is the actual skill.*
   - **Habit to build: unit-check every intermediate value.** When a number's units don't match its label, something is wrong. This matters more later — mA, µF, kΩ, and MHz get juggled constantly in embedded work, and dimensional analysis catches errors that look perfectly reasonable as bare numbers.
   - The same 1.5 was used **correctly** elsewhere: 2 V × 1.5 mS = 3 mA is Ohm's law with conductance, and dimensionally perfect. The idea was right; only the label was wrong.
2. ⚠️ **Numeric coincidences ate a lot of time.** These values collide three separate ways:
   - R1 = 1 kΩ **and** the load = 1 kΩ
   - R2∥R_load = 667 Ω **and** R1∥R2 = 667 Ω (two different quantities, same number by accident)
   - V_out = 2 **V** and the load current = 2 **mA**
   - **Takeaway: deliberately pick values that can't collide.** Re-running with a 470 Ω load gives V_out = 1.38 V, I_R1 = 3.62 mA, I_R2 = 0.69 mA, I_load = 2.93 mA — no two alike, nothing to confuse. This is a real debugging technique and it comes back the first time a sensor reads 255 and the question is whether that's a measurement or an uninitialized byte.
3. **Layout:** first build was a rectangular loop with the output stranded on the top wire. Electrically fine, hard to read. Rebuilt vertically (rail top → R1 → node → R2 → ground) and everything got easier — including spotting where the load attaches. **Draw schematics the conventional way even when the unconventional way works.**

**Conceptual gain — Thévenin, informally.** The reason output resistance is R1∥R2 (when R1 and R2 are visibly in *series*): an ideal voltage source has zero internal resistance, so from a resistance standpoint it behaves like a wire. Looking back into the divider from the output node, the 5 V rail is effectively tied to ground, which puts R1 and R2 both between V_out and ground — in parallel. Solve for voltage → series; ask how stiff the output is → parallel. ⚠️ Thought experiment only; don't actually short a source in the sim. This is the doorway into **Thévenin/Norton equivalents** (Vol. I Ch. 10).

---

## Lab log — NPN Switch (Lab 4)

**Status:** core objective complete. Part: XN2222-type NPN (2N2222 family) in Falstad.

**Design — deviated from §E.3's worked example on purpose, at a lower LED current:**

- Target I_C = **10 mA** → I_B = I_C/10 = **1 mA**
- R_C = (5 − 2.0 − 0.2)/0.010 = 280 Ω → **330 Ω** *(rounded **UP** — LED rule)* → predicted I_C = 2.8/330 = **8.5 mA**
- R_B = (3.3 − 0.7)/0.001 = 2600 Ω → **2.2 kΩ** *(rounded **DOWN** — base rule)* → predicted I_B = 2.6/2200 = **1.18 mA**
- Forced β = 8.5/1.18 = **7.2** — far below the datasheet's 100 min hFE, so solidly saturated ✓
- Power: R_C ≈ 24 mW · R_B ≈ 3 mW · transistor ≈ 4.8 mW — all ≪ 250 mW ✓

| Quantity | Predicted | Measured | Δ |
|---|---|---|---|
| I_B | 1.18 mA | 1.204 mA | +1.9 % |
| I_C | 8.5 mA | 8.672 mA | +2.0 % |
| V_CE (on) | 0.2 V | 0.549 V | sim artifact — see below |
| V_CE (off) | ~5 V | 4.991 V | ✓ |
| **Forced β (I_C/I_B)** | **7.2** | **7.2** | ✓ |

**The result that is the lab:** the "GPIO" supplies **1.2 mA** while the LED draws **8.7 mA**. A **7×** current ratio. At a relay's 500 mA the same ratio is the difference between a working board and a destroyed pin.

**Reconciling the 2 % gap — work backward from the measurement, don't guess:**

- Voltage across R_B = 1.204 mA × 2200 = 2.649 V → so V_BE = 3.3 − 2.649 = **0.651 V**, not the assumed 0.700 V. That single assumption is the entire base-loop discrepancy.
- Voltage across R_C = 8.672 mA × 330 = 2.862 V → leaves 5 − 2.862 − 0.549 = **1.589 V** for the LED, vs. the 2.0 V nominal. Same cause: V_f is exponential, so at lower current the drop is lower.
- **Standard adopted: hand calculations use nominal constants (0.7 / 2.0 / 0.2 V) that are deliberately approximate. Agreement within ~5 % means the design is working.** Chase a discrepancy only when it's large enough to change a decision — and the method for chasing one is exactly the above: reverse the arithmetic to find which assumption was off.

**⚠️ Simulator limits found (worth remembering — Falstad is not a datasheet):**

- Measured V_CE(sat) = 0.549 V, but a real 2N2222 at 8.7 mA with 1.2 mA base drive lands near 0.1–0.2 V. Falstad's transistor model runs high.
- Saturation test that still works regardless: **V_BE − V_CE = 0.651 − 0.549 = +0.102 V.** Positive ⇒ the base-collector junction is forward biased ⇒ saturated by definition. (Negative would mean active region.) Shallow, but on the right side of the line.
- Falstad's model omits the internal base/emitter resistance that makes V_BE(sat) climb with current, so it will **never** show that effect no matter how hard the base is driven.

**Mistakes logged:**

1. ⚠️ **Base shorted to emitter.** A stray rectangular wire path ran from the base node down and back into the emitter, tying the base to ground through the emitter connection. Transistor stayed off with the logic input high.
   - **How it was caught, without touching the schematic:** the scope on R_B read **Max = −3.3 V** — the *entire* input voltage dropping across the base resistor, which can only happen if its far end is at 0 V. Corroborated by V_CE = 4.991 V (nearly the whole rail across an off transistor) and by the collector-side readings of **3.36 nV** across R_C and **8.978 mV** across the LED — no current in the collector loop at all.
   - **Pattern: when the transistor is off, the scope readings tell you *why* before the schematic does.** Full supply across the transistor + ~0 across everything else = no base drive. Then look for what's holding the base down.
2. ⚠️ **Used V_BE(sat) = 0.85 V from a source written for a 2N3904.** The instinct was right — V_BE(sat) genuinely exceeds V_BE(active) — but the number came from the wrong operating point *and* the wrong part. 0.65–0.85 V is a **min-to-max spread across manufactured parts**, not a current-dependent slide; the genuinely current-dependent high figures (~1.2 V) are quoted at 150 mA.
   - The part's own datasheet listed **V_BE(sat) = 0.75 V at I_C = 10 mA, I_B = 1 mA** — an exact match to this design, which almost never happens. Should have been used over the generic 0.7 V.
   - Prediction accuracy: 0.85 V → 1.11 mA (7.5 % low) · 0.70 V → 1.18 mA (1.9 % low) · measured 1.204 mA.
   - **The error was in the safe direction:** overestimating V_BE underestimates I_B, which picks a *smaller* R_B, which gives *more* base drive. For a switch, more drive is safe.
   - **Standing rule: a datasheet number without its test conditions is meaningless.** Read the conditions column first.
3. **Built with un-designed values before fixing them** (R_C = 1 kΩ, then 330 Ω; R_B = 2.2 kΩ) and spent time wondering why measurements didn't match a calculation done for different parts. **Verify the schematic matches the design sheet before debugging the physics.**
4. **Logic Input sat at L (0 V)** while looking for a fault. The circuit was correct; the input was just low. Check the drive state before assuming a wiring bug.

**Falstad notes for next time:**

- "GPIO" is not a component. **Draw → Logic Gates, Input and Output → Add Logic Input**, then right-click → Edit to set the high voltage to 3.3 V (defaults to 5 V, which silently breaks the R_B math). Click it while running to toggle H/L.
- Simpler alternative when the toggle isn't needed: a 1-terminal voltage source at 3.3 V straight into R_B. Always on, still gives the I_B vs. I_C reading.
- Transistor orientation: verify with the §E.1 mnemonic — the arrow is on the **emitter** and points **out** for NPN.
- All ground symbols are one net (§G.4). Drop a fresh ground under the pull-down instead of routing a wire back.

**Conceptual gains:**

- **A transistor switch is two loops sharing the emitter.** Base loop (small, from the GPIO) and collector loop (large, from the rail). Each gets its own KVL and its own resistor. This is what makes the five-step recipe feel inevitable rather than arbitrary.
- **The base loop is an LED circuit in disguise.** R = (V_source − V_diode)/I_target either way — the B-E junction is a diode with a fixed-ish drop and the resistor absorbs the leftover. Same structure as §D.2.
- **P = VI is the general form; P = I²R is the special case** that requires Ohm's law to hold. A saturated transistor holds a roughly fixed voltage rather than obeying Ohm's law, so its dissipation is V_CE × I_C.
- **The cost of not saturating, in numbers:** at 8.7 mA, V_CE = 0.549 V → 4.8 mW; the same current half-on at V_CE = 2.5 V → 21.7 mW, **4.5×** the heat. Scaled to a relay at 500 mA: 100 mW saturated vs. **1.25 W** half-on. That is the entire argument for forced β.

---

## Hooks to later weeks

- τ = RC → **Week 3** button debounce (10 k + 100 nF ≈ 1 ms) and the hardware-vs-software debounce comparison
- Cap = short at t=0 → **Week 3/4** decoupling caps at every IC power pin; **Week 20** KiCad placement rules (as close to the pin as possible, because trace inductance is the thing being defeated)
- ADC input settling as an RC against source impedance → **Week 7** pot→ADC→PWM, where the divider's R1∥R2 **is** the R in that time constant. Week 1's loaded-divider work and Week 2's RC chapter meet exactly here.
- Universal time constant formula → **Week 9** motor spin-up/coast curves; anything first-order
- Flyback diode across an inductive load → **Week 9** motor/relay driving — non-optional, kills transistors when omitted
- Schottky low V_f → reverse-polarity protection on any board fed from a barrel jack or battery
- LED V_f vs. rail headroom → **Week 5+** every status indicator; and the reason 3.3 V boards use red/green indicators, not blue
- GPIO current budget (per-pin **and** total) → **Week 5** first STM32 bring-up; the reason a transistor appears the moment a load exceeds an indicator LED
- Forced β = 10 and base pull-downs → **Week 9** motor driver, **Week 11** any level-shifting
- Floating-pin behavior during reset → **Week 4** floating inputs, and the standing rule that every MCU-driven switch gets a pull-down
- V_GS(th) and "logic level" → **Week 9** MOSFET selection; the IRF540-on-3.3 V mistake is the one to have already made in simulation
- R_DS(on) vs. V_CE(sat) → the crossover current where MOSFETs beat BJTs; comes back in power-path design
- Buck vs. LDO decision → **ebike project**: a 48 V pack down to 5 V is 10% efficient linear — a buck is mandatory, not preferred. Same math governs the DeWalt-battery/inverter off-grid charging setup.
- Regulator dropout vs. a sagging battery → **Week 12+** battery-powered builds; a 3.7 V LiPo at 3.4 V doesn't clear an AMS1117 for 3.3 V out
- Quiescent current → **Week 12+** sleep-mode power budgeting; the same µA thinking as Week 1's weak-pull-up sizing
- Closed loop (reference + error amp + feedback) vs. open loop → the conceptual seed of **control systems**; also why a divider is a reference and never a supply
- ⚠️ Regulator input/output cap requirements (type and ESR, not just value) → **Week 20** BOM decisions; the wrong cap makes the loop oscillate
- Ceramic cap DC bias derating (X7R/Y5V losing half its value under load) → **Week 20** part selection; C0G/NP0 where τ must be repeatable
- Junction dots and net labels → **Week 20** KiCad; ERC single-node-net warnings are the compiler catching a typo'd variable name
- Schematic-reading discipline (power rails first, recognize the idioms) → **Week 20** reading vendor reference designs, and **Week 24** board bring-up
- Absolute Maximum vs. Recommended Operating → general datasheet literacy; the distinction that separates parts that die slowly from parts that don't
- Resistor derating (2×) → standing habit; same instinct as thermal headroom anywhere
- Unit-checking every intermediate → standing debugging habit, per the Lab 1 log; the cheapest error detector available
- Deliberately non-colliding test values → standing debugging technique, from bench to firmware
- Predicted/measured/delta tables → the standing lab format for the rest of the 26 weeks
- ⚠️ Datasheet **conditions columns** (every V_BE(sat), V_CE(sat), β figure has an I_C/I_B attached) → standing datasheet-literacy habit, from Lab 4's 0.85 V error
- ⚠️ Simulator models are not datasheets (Falstad's V_CE(sat) runs high, omits V_BE(sat) rise) → **Week 24** bring-up, where the real part disagrees with the sim
- Reverse-the-arithmetic debugging (work backward from a measurement to find which assumption was off) → standing technique, from Lab 4's 2 % reconciliation
- Scope readings diagnose *why* before the schematic does (full supply across an off transistor + ~0 elsewhere = no base drive) → standing bench technique
- ~5 % agreement is success; nominal constants are approximations → standing standard for every lab from here
- Thévenin intuition (short the source, look back) → **Vol. I Ch. 10** network theorems; the formal version of the Lab 1 output-resistance argument
