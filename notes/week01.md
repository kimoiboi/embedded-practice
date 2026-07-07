# Week 1 Notes — DC Theory Foundations
**Source:** All About Circuits, Vol. I — Ch. 1 (Basic Concepts of Electricity), Ch. 2 (Ohm's Law), Ch. 5 (Series & Parallel Circuits), Ch. 6 (Divider Circuits & Kirchhoff's Laws)
**Habit:** every worked example gets rebuilt in Falstad. Hover wires for current, nodes for voltage, check against hand math.

---

## Chapter 1 — Basic Concepts of Electricity

### 1.1 Charge — what it physically is

- Matter = atoms = protons (+), neutrons (0), electrons (−). Protons/neutrons are locked in the nucleus; **electrons are the mobile particle** — they can be dislodged with far less energy. All of electronics is electron bookkeeping.
- Proton count defines the element; electron count defines the **charge state**. Equal numbers → net charge zero. Electron surplus → negatively charged; electron deficit → positively charged.
- Like charges repel, opposite charges attract, and this force acts at a distance.
- **Static electricity** = a charge imbalance created by physically transferring electrons (e.g., rubbing two materials), where the displaced electrons then just sit there on an insulator.
- **Unit of charge:** the coulomb (C) ≈ 6.25 × 10¹⁸ electrons. One electron carries the *elementary charge*, ≈ 1.6 × 10⁻¹⁹ C.
- Historical gotcha: Franklin guessed the direction of charge transfer backwards, which is why electrons ended up labeled "negative." The naming stuck. This is the root of the conventional-vs-electron-flow mess in §1.7.

### 1.2 Conductors, insulators, electron flow

- **Conductors** = materials whose outer electrons are so loosely bound they wander freely between atoms ("free electrons"). Metals, graphite, dirty water. Silver is the best; copper/aluminum are the practical wire choices.
- **Insulators** = electrons stay put. Glass, rubber, plastic, dry air, pure water.
- Conductivity is a spectrum, not a binary — think transparency to light: glass vs. frosted plastic vs. brick.
- Conditions change conductivity: most metals conduct *worse* when hot, *better* when cold (this becomes the nonlinear-lamp story in Ch. 2). Air becomes conductive when ionized (lightning).
- **Current** = free electrons moving in a coordinated direction. Individual electrons drift slowly, but the *effect* propagates near light speed — the marble-filled-tube picture: push a marble in one end, one pops out the other end instantly, even though no single marble moved far.
- Flow requires an unbroken conductive path. Break the path anywhere → flow stops everywhere.

### 1.3 Circuits

- A continuous flow can't run on a "source bucket" and "destination bucket" — they'd have to be infinite. The fix is the **circuit**: a closed loop, so each electron pushes the one ahead of it forever.
- **The break-location rule:** any discontinuity, anywhere in the loop, stops current *everywhere* in the loop. There's no "partial" flow in a single loop.
- Vocabulary: **closed circuit** = complete path, current possible. **Open circuit** = broken path, no current. A **switch** is just a device for opening/closing on purpose. (Watch the words: an *open* switch blocks flow, a *closed* switch permits it — opposite of doors.)

### 1.4 Voltage and current — the core mental model

**The water-reservoir analogy (internalize this):**

| Water system | Electricity |
|---|---|
| Pump lifting water uphill | Battery / voltage source |
| Height of the reservoir | Voltage |
| Water flow rate through pipe | Current |
| Pipe restriction / waterwheel | Resistance |
| Pressure difference between two heights | Voltage *between two points* |

- **Voltage** = potential energy **per unit charge**. It's the "push" available to move electrons. Formally: the work needed to move a unit of charge between two locations against the electric force.
- **Voltage is ALWAYS between two points.** A single point has no voltage, the same way a single height has no "drop." This is why it's called a voltage *drop*, and why the meter has two probes. If someone says "the voltage at node X," there's an implied reference (usually ground).
- Voltage can exist **without** current: a disconnected battery still has 9 V across its terminals. Charge is poised, nothing flows. (Reservoir full, no return pipe.)
- Connect a conductive loop → the voltage drives a **current**: continuous, uniform electron flow. One direction only = **DC** (this whole volume); alternating direction = AC (later).
- **Current is the same at every point in a single loop.** Same electrons/second past any cross-section, regardless of wire length or thickness. (Marbles in a hula-hoop — nowhere for them to pile up.)
- **Break a circuit → the full source voltage appears across the break.** Nothing flows, so nothing drops anywhere else; all the "push" waits at the gap. This is a big deal for troubleshooting later: huge voltage across two points that should be connected = open failure between them.
- **Polarity** = the +/− orientation of a voltage. Also relative between two points — the same physical point can be "+" in one measurement and "−" in another depending on what it's referenced against.
- Voltage sources beyond rubbing things together: chemical reaction (battery), light (solar cell), magnetism + motion (generator/alternator).

### 1.5 Resistance

- **Resistance** = opposition to current. Electrons moving against it generate heat (friction analogy). Depends on material, cross-sectional area, and temperature.
- A lamp filament is *concentrated* resistance: same current as the wires, but far more opposition → heat → white-hot glow. The connecting wires (low R) barely warm up.
- **Short circuit** = source terminals joined by nearly zero resistance → enormous current, dramatic energy release. Dangerous. This is why the bare-wire loop in §1.4 is a thought experiment, not a build.
- Open vs. closed circuit vocabulary applies here too — a switch works by inserting/removing an air gap (air = insulator) anywhere in the loop, which is why a wall switch can control a lamp across the room.

### 1.6 Voltage and current in a practical circuit

- One loop: current identical everywhere (through battery, wires, lamp).
- But **voltage between points varies with the resistance between them**. Across the lamp (high R): almost the full battery voltage. Across a stretch of wire (≈0 R): almost nothing.
- Waterwheel version: big pressure difference across the wheel (where energy is extracted), nearly none along the open channels.
- This asymmetry — *current uniform, voltage distributed by resistance* — is the seed of voltage dividers (Week 2) and Kirchhoff's Voltage Law (Ch. 6).

### 1.7 Conventional vs. electron flow notation

- **Electron flow** (physical truth): electrons exit the battery's − terminal, travel the loop, return to +.
- **Conventional flow** (engineering standard): current drawn from + to −, following Franklin's original (wrong) guess.
- Neither changes any math. Ohm's Law, KVL/KCL — all valid either way, as long as you're consistent.
- **The practical reason conventional flow wins:** semiconductor symbols (diode, transistor arrows) all point in the conventional direction. The diode arrow points the way conventional current flows through it.
- ⚠️ *Note for this book:* AAC is illustrated in **electron flow** notation. Most datasheets, EE courses, and schematics you'll meet use **conventional**. Decide now: think in conventional flow, and remember AAC's arrows are drawn the other way.
- A **diode** = one-way valve for current: near-zero resistance one direction, near-infinite the other. Polarized device (direction matters). Lamps, resistors, switches = nonpolarized (direction irrelevant).

---

## Chapter 2 — Ohm's Law

### 2.1 Quantities, units, symbols — the table to memorize

| Quantity | Symbol | Unit | Abbrev. | Defined as |
|---|---|---|---|---|
| Current | I | ampere | A | 1 coulomb of charge passing a point per second |
| Voltage | E (or V) | volt | V | 1 joule of energy per coulomb of charge |
| Resistance | R | ohm | Ω | 1 V across it drives 1 A through it |
| Charge | Q | coulomb | C | ≈ 6.25 × 10¹⁸ electrons |
| Energy | — | joule | J | work of 1 newton over 1 meter |

- "I" = intensity of flow; "E" = electromotive force. E and V are interchangeable (some texts use E for sources, V for drops).
- Lowercase (i, e, v) = instantaneous values; uppercase = steady DC values.
- A 9 V battery hands each coulomb of charge 9 joules of energy to spend around the loop.

### 2.2 Ohm's Law

**E = I·R  →  I = E/R  →  R = E/I**

- Ohm's discovery (1827): current through a metal conductor is **directly proportional to voltage** across it, at a given temperature.
- Know any two of the three, compute the third. The E-over-I-R triangle is a crutch; just memorize E = IR and do the algebra.
- Water intuition: pressure ↑ with same restriction → flow ↑. Same pressure, restriction ↑ → flow ↓. Same flow with less restriction → less pressure needed.

**Worked examples from the chapter (rebuild each in Falstad):**
1. 12 V battery, 3 Ω lamp → I = 12/3 = **4 A**
2. 36 V battery, 4 A flowing → R = 36/4 = **9 Ω**
3. 2 A through 7 Ω → E = 2×7 = **14 V**

### 2.3–2.4 Power

**P = I·E** (watts) — plus the substitutions via Ohm's Law:

**P = I²R  |  P = E²/R**

- **Power = rate of doing work.** Voltage is work-per-charge; current is charges-per-second; multiply → work-per-second = watts.
- Neither voltage nor current alone is power: open circuit (V, no I) → 0 W. Superconducting loop (I, no V) → 0 W.
- Analogy: engine power = torque × speed. High-torque tractor and high-RPM motorcycle can both make 100 hp. High-V/low-I and low-V/high-I circuits can dissipate identical watts.
- **The square matters:** double the voltage across a fixed R → current doubles too → power ×4. (Chapter example: 18 V/3 Ω = 108 W; 36 V/3 Ω = 432 W.) This is why P = E²/R and P = I²R have squares in them.
- Strictly, the power equations are **Joule's Law** (1841), not Ohm's — they're just always taught together.
- 1 hp = 745.7 W (trivia, and why EU car specs read in kW).

### 2.5 Resistors

- Purpose-built components providing a precise, stable R. Zig-zag schematic symbol (or a rectangle box); labeled R1, R2, ... A diagonal arrow through any symbol = variable (potentiometer).
- **Two ratings, independent of each other:** resistance (Ω) and power dissipation (W). Physical size tracks the *wattage*, not the ohms. Most small-electronics resistors are ¼ W — your kit's are.
- **Design rule from the chapter's closing example:** 10 V, 2 A → R = 5 Ω, P = 20 W. Spec a resistor rated *at least* the dissipated power or it overheats and fails. (Week 2 preview: this is the "when a ¼ W resistor smokes" lesson.)
- "**Load**" = generic term for anything useful consuming power; schematics often draw a resistor symbol as a stand-in for one.

### 2.6 Nonlinear conduction — where Ohm's Law bends

- Ohm's Law assumes R is constant. For most components across normal ranges, it is → I vs. E plots a straight line ("linear").
- **Incandescent filament:** resistance climbs steeply with temperature. More voltage → more current → hotter → more R → current gains flatten. The I/E curve bows over. You can't use one R value for that lamp.
- **Gas ionization:** air insulates until a threshold voltage rips electrons off its molecules; then it conducts hard. Near-zero current, then a cliff. This is lightning, and why bolts are pulses: conduct → charge depletes → voltage falls below threshold → air de-ionizes → repeat.
- Solid insulators can break down too, but often **stay damaged** (breakdown voltage permanently lowered) — a failure mode in high-voltage wiring.
- **Varistor:** engineered to do repeatable breakdown — high R until a firing voltage, then R collapses. (Surge protection.)
- **Negative resistance:** some devices (tunnel diodes, tetrode tubes) pass *less* current as voltage rises in certain ranges. Exotic, just know it exists.
- Honest framing: "R = E/I" is really a *definition of resistance*, and a "law" only for materials whose R holds still. Assume stable R in this book unless told otherwise.

### 2.7 Circuit wiring — electrically common points

- Wires are assumed **zero resistance** → they drop zero volts (E = I×0 = 0) no matter the current.
- Points joined only by wire are **electrically common**: same voltage relative to anywhere else in the circuit. You can stretch, shorten, or reroute wires freely — only the *sequence of component connections* matters.
- Consequence: measuring across the battery = measuring across the resistor, if wires connect them directly. Any pair of points spanning the battery-to-resistor gap reads the full source voltage.
- **Troubleshooting gold:** two points that *should* be common must read ≈0 V between them. Substantial voltage between them → the connection is broken somewhere ("open failure"). This is half of what your multimeter is for in Week 3.
- Real wires have a little resistance; the rules hold "to a large degree, not an absolute degree." Matters in power wiring; ignorable on a breadboard.

### 2.8 Polarity of voltage drops

- Current through a resistance creates a voltage drop with a definite orientation: **(electron-flow view) the end current enters is −, the end it exits is +.**
- Equivalent conventional-flow rule: current enters the + end, exits the −. Same physics, same markings.
- Ohm's Law itself uses magnitudes only — no negative numbers for E, I, R. Polarity bookkeeping becomes essential in Ch. 6 (KVL with multiple sources/resistors).

### 2.9 Circuit simulation (SPICE)

- The chapter demos SPICE: describe the circuit as a text netlist (components + shared node numbers), run, read node voltages / source currents / power. Node 0 = reference.
- Netlists confirm everything above: 10 V / 5 Ω → 2 A, 20 W; sweep V 0→100 and current tracks at exactly E/5.
- *For this plan:* Falstad gives the same insight interactively — the takeaway is the concept of **nodes** (electrically common points get one label), which returns in Week 20 when KiCad calls them "nets."

---

## Chapter 5 — Series and Parallel Circuits

### 5.1 The two topologies — definitions that generate all the rules

- **Series** = components connected end-to-end, forming **exactly one path** for electrons. That's the entire definition; the three series "rules" below are footnotes to it (the author says this explicitly, and he's right).
- **Parallel** = all components connected **between the same two sets of electrically common points** — never more than two sets in a purely parallel circuit. Each component's individual path is a **branch**.
- Ch. 2's "electrically common" idea does the identification work: trace which points are joined by bare wire. Top nodes all common, bottom nodes all common, everything strung between them → parallel. One unbroken chain → series.
- **Series-parallel hybrids** exist (e.g., R1 in series with R2∥R3) — full treatment comes later, but you spot them the same way: trace paths and common-point sets.
- Subscripts (R₁, R₂…) are *names*, not values.

### 5.2 Series circuits — the three rules

Worked example (rebuild in Falstad): 9 V battery, R1 = 3k, R2 = 10k, R3 = 5k in series.

1. **Current is identical through every component.** One path — the marble tube again. I_T = I₁ = I₂ = I₃.
2. **Resistances add:** R_T = R₁ + R₂ + … — more opposition stacked in the single path. Here: **18 kΩ**.
3. **Voltage drops sum to the source voltage:** E_T = E₁ + E₂ + …

- Solve order: R_T = 18k → I = 9 V / 18k = **500 µA** everywhere → drops via E = I·R: **1.5 V, 5 V, 2.5 V** (sum = 9 V ✓).
- ⚠️ **The Ohm's-Law context trap** (the chapter hammers this): you may *not* compute 9 V / 3 kΩ and call it anything. Every E, I, R in one equation must refer to the **same two points**. 9 V spans the whole string; 3 kΩ is one component. Mix contexts and the number describes nothing real.
- **The table method — adopt it permanently:** columns R1 | R2 | R3 | Total, rows E / I / R (+ P). **Ohm's Law only within a vertical column; series/parallel rules only along horizontal rows.** It's a mechanical guardrail against the context trap.

### 5.3 Parallel circuits — the three rules

Worked example: 9 V battery, R1 = 10k, R2 = 2k, R3 = 1k in parallel.

1. **Voltage is identical across every component** — only two sets of common points exist, and the voltage between them is one number. E_T = E₁ = E₂ = E₃.
2. **Branch currents add:** I_T = I₁ + I₂ + … — river splitting into streams and merging back. Here: 0.9 m + 4.5 m + 9 m = **14.4 mA**.
3. **Total resistance diminishes:** R_T = 1/(1/R₁ + 1/R₂ + 1/R₃) = **625 Ω** — *less than the smallest branch* (1k). Exact opposite of series.

- Note the opposite solve order: parallel starts at the **branches** (each branch's V and R are known → I immediately), series starts at the **total**. The topology tells you where Ohm's Law is legal first.

### 5.4 Conductance — where the weird reciprocal formula comes from

- **G = 1/R** — "ease of flow" instead of opposition. Unit: **siemens (S)**, formerly the **mho** ("ohm" backwards). Always "siemens," never "siemen" — it's a surname.
- In parallel, conductances simply **add** — every extra branch is another way through: G_T = G₁ + G₂ + …
- Substitute G = 1/R into that sum and solve for R_T → the reciprocal formula falls out. It isn't arbitrary; it's "parallel paths add ease," expressed in resistance units.
- Two-resistor shortcut: R_T = R₁R₂/(R₁ + R₂); equal pair → half. (Week-1 self-check #2 ✓.)

### 5.5 Power calculations

- Per component: P = I·E = I²R = E²/R, computed *within that component's column* (context rule again).
- **Power is additive in ANY configuration** — series, parallel, whatever: P_T = P₁ + P₂ + … Conservation of energy doesn't care about topology.
- Bonus: that makes the P row a free **cross-check** on a solved table — if component powers don't sum to total power, there's a mistake somewhere, guaranteed.

### 5.6 Correct use of Ohm's Law — the sermon, condensed

- **The one rule:** every variable in a single Ohm's-Law equation must be common to the **same two points** — voltage *across* them, current *through* them, resistance *between* them, power dissipated *by what's between* them.
- Table discipline: Ohm's Law vertically, series/parallel rules horizontally, always.
- Verification habit: solve, then work *backwards* to the given values, or solve one quantity a second way. Cheap insurance.

### 5.7 Component failure analysis — qualitative reasoning (the troubleshooting seed)

Method: re-draw the circuit with the failed part as ≈0 Ω (**shorted**) or ≈∞ Ω (**open**), then re-reason every value. Series example (9 V, 100/300/50 Ω — healthy: 450 Ω, 20 mA, drops 2/6/1 V):

| Fault | R_T | I | Voltage picture |
|---|---|---|---|
| R2 **shorts** | 450 → 150 Ω | 20 m → 60 mA | R2 drops **0 V**; the survivors' drops **rise** (6 V, 3 V) — they now split the full 9 V |
| R2 **opens** | → ∞ | **0 everywhere** | good resistors drop 0 V; the **full 9 V appears across the open** |

- The open row is Ch. 1's break-location rule, quantified. **Troubleshooting gold: full supply voltage measured across two points = the open failure is between those points.**

Parallel example (9 V, 90/45/180 Ω):

- **Branch opens** → that branch's current → 0 and total current drops; **the other branches don't notice** — the source holds their voltage constant. This is house wiring: lamps in parallel, so one switch doesn't dim the room.
- **Branch shorts** → theoretically infinite current (I = E/0). Reality: every real source has **internal resistance**, which suddenly dominates — nearly all the voltage drops *inside the source*, every branch voltage **collapses**, and things get hot. The "simple parallel circuit" was secretly series-parallel all along.
- Never deliberately short a source — even if nothing nearby gets hurt, the source likely will.
- Field statistic worth remembering: **resistors fail open far more often than shorted**, and almost never unless physically/electrically overstressed.

### 5.8 Building circuits — the fabrication menu

- **Alligator-clip jumpers:** fine for battery + one resistor; awkward and fragile beyond that.
- **Solderless breadboard** (Week 3's home): spring clips under the holes, **joined in columns of 5**; power rails run lengthwise and **often split mid-board** — verify with continuity before trusting them. Temporary only, and **< 1 A** (tiny clip contact area overheats).
- **Soldering** = low-temperature welding with tin/lead or tin/silver alloy. Good joint = shiny cone. (Week 4's skill block.)
- **Wire-wrapping:** tightly wrapped small-gauge wire; the tension itself makes a sound electrical joint. Solder-free permanence.
- **Terminal strips** (a.k.a. barrier strips): the industrial standard — screw-clamped metal bars; robust, reworkable, good for permanent *and* temporary work.
- The schematic→terminal-strip translation exercise is the point: schematics are drawn for *readability*, real layouts aren't — "stretching wires" mentally is a core skill.
- Industry conventions to file away: **electrically common wires share one number label**, and terminal points get TB-numbers referenced back onto the schematic, turning it into a *map* of the physical build. Same concept as SPICE nodes → (Week 20) KiCad **nets**.

---

## Chapter 6 — Divider Circuits and Kirchhoff's Laws

### 6.1 Voltage dividers — series circuits with a job title

Worked example: 45 V across 5k + 10k + 7.5k in series (R_T = 22.5k, I = 2 mA):

- Drops = **10 V, 20 V, 15 V** — each **directly proportional to its resistance**, because the current is identical everywhere and E = I·R does the rest. R2 = 2×R1 → E_R2 = 2×E_R1.
- Crank the supply to 180 V → drops become 40/80/60 V, but the **ratios never move**: E_R1/E_T = 0.2222 at 45 V and at 180 V. **The division ratio is set by resistance alone.**
- So skip the current calculation entirely — the **voltage divider formula:**

  **E_Rn = E_T · (Rn / R_T)**

  Derivation is one substitution: E_n = I·R_n with I = E_T/R_T. (Week 2's self-check asks for exactly this derivation in two-resistor form: Vout = Vin·R₂/(R₁+R₂).)
- **Potentiometer** = the divider as a single component: resistive strip + sliding **wiper**. End-to-end resistance is constant; the wiper splits it into the divider's two legs. Wiper at 50% → exactly half the applied voltage — *regardless* of the applied voltage or the pot's total ohms. Name makes sense: it *meters potential*. Variants: rotary, linear/slide, **trimpot** (turn-screw fine adjustment), multi-turn precision units (Helipot).
- Use case: "dial up" any voltage below the supply for a sub-circuit.
- ⚠️ **Plan-note (Week 2 lab, not in this chapter): that only holds unloaded.** Attach a load and its resistance parallels the bottom leg → the ratio changes → Vout sags. Dividers make *reference voltages*; they don't *power* things. Watch it happen in Falstad with the 3.3 V-from-5 V divider + 1k load.

### 6.2 Kirchhoff's Voltage Law (KVL)

> **"The algebraic sum of all voltages in a loop must equal zero."** — Gustav Kirchhoff, 1847

- **Notation to internalize:** E₂₋₁ = the voltage at point 2 *referenced to* point 1 = what a digital voltmeter reads with **red lead on 2, black on 1** — sign included.
- The demo: walk the 45 V series loop with consistent lead orientation (red always on the point ahead): +45, −10, −20, −15 → **sum = 0**. Start at any point, walk either direction — still 0.
- Why it *must* be true: any loop ends where it started, and the voltage between a point and itself (E₂₋₂) is 0. Total climb = total drop. The resistor drops are polarized *opposite* the source (they oppose the push), which is what makes the signs cancel.
- **Scope — the part people underestimate:**
  - Works for **any topology**: series, parallel, series-parallel, even a sealed black box of components.
  - The "loop" is any path that returns to its start — it does **not** have to be an actual current path (the book traces 2-3-6-3-2 back and forth through the middle of a parallel circuit; sum is still 0).
- **The workhorse application — unknown voltages:** in the two-series-circuits-joined-by-one-wire example, want E₄₋₃? Pick any loop through known drops and sum to zero: E₄₋₃ + 12 + 0 + 20 = 0 → **E₄₋₃ = −32 V**. The minus sign just means the assumed meter orientation was backwards — point 3 is actually + with respect to point 4. Starting from E₃₋₄ instead gives +32 V; **neither is wrong**, both say the same physical thing.
- The entire skill is **sign discipline**: pick a walking direction, write down what the imaginary voltmeter reads (red on the point ahead, black behind), never improvise mid-loop.

### 6.3 Current dividers — parallel circuits with a job title

Worked example: 6 V across 1k ∥ 3k ∥ 2k (R_T = 545.45 Ω): branch currents **6 / 2 / 3 mA**, total 11 mA.

- Branch current is **inversely** proportional to branch resistance (same V everywhere, I = E/R): R1 is half of R3 → carries twice the current.
- Ratios fixed by resistance alone, again: quadruple the supply and I_R1/I_T stays 0.54545.
- **Current divider formula:**

  **I_n = I_T · (R_T / Rn)**

  — the fraction is **flipped** relative to the voltage divider.
- **The keep-them-straight trick** (the chapter's own): a *divider* ratio must be **< 1**. Series: R_T is bigger than any Rn → the fraction must be Rn/R_T. Parallel: R_T is smaller than any Rn → the fraction must be R_T/Rn. If your fraction exceeds 1, you flipped it.
- Application: the **meter shunt** — size a parallel resistor so a known fraction of a measured current routes through the sensitive movement. (Foreshadows Week 19: the shunt inside your multimeter's current range is where *burden voltage* lives.)

### 6.4 Kirchhoff's Current Law (KCL)

> **"The algebraic sum of all currents entering and exiting a node must equal zero."**

- Plumbing version: every node is a tee fitting; no leaks → flow in = flow out. I_entering = I_exiting, rewritten with signs: entering (+), exiting (−), sum = 0. Which sign means which is **arbitrary — just stay consistent**.
- The node-3 drill: 2 mA and 3 mA enter, one unknown current: 2m + 3m + I = 0 → I = **−5 mA** → 5 mA *exiting*. The sign carries the direction, exactly like KVL's.
- Big picture: **KVL + KCL are Ohm's Law's equals** — memorize them at the same rank. They're the engine of network analysis later, and together with §5.1's definitions they *generate* the six series/parallel rules: KVL around a single loop → series drops add; KCL at a two-node circuit → parallel branch currents add.
- Plan's phrasing, which is the right mental compression: **"energy around a loop sums to zero; current into a node equals current out."**

---

## Formula sheet

```
Ohm's Law:      E = I·R        I = E/R        R = E/I
Power:          P = I·E        P = I²R        P = E²/R
Charge/current: 1 A = 1 C/s
Energy/voltage: 1 V = 1 J/C

Series:         I_T = I₁ = I₂ = …      R_T = R₁ + R₂ + …      E_T = E₁ + E₂ + …
Parallel:       E_T = E₁ = E₂ = …      I_T = I₁ + I₂ + …      R_T = 1/(1/R₁ + 1/R₂ + …)
Two in ∥:       R_T = R₁R₂/(R₁+R₂)     (equal pair → half)
Conductance:    G = 1/R  [siemens]     parallel: G_T = G₁ + G₂ + …
Power:          additive in ANY topology: P_T = P₁ + P₂ + …

Voltage divider: E_Rn = E_T·(Rn/R_T)   (series — ratio < 1, small over big)
Current divider: I_n  = I_T·(R_T/Rn)   (parallel — ratio < 1, small over big)

KVL: Σ voltages around any closed loop = 0   (signs from meter-lead orientation)
KCL: Σ currents at any node = 0              (entering +, exiting −, be consistent)
```

## Week 1 self-check — worked

1. **Current through 220 Ω across 5 V?** I = E/R = 5/220 ≈ **22.7 mA** ✓ (this is *the* LED-resistor ballpark)
2. **Two 1 kΩ in parallel?** Equal resistors halve: **500 Ω**. (Ch. 5: R_T = 1/(1/R₁+1/R₂), or the two-resistor shortcut R₁R₂/(R₁+R₂) = 1M/2k = 500 Ω. Sanity check: below the smallest branch ✓.)
3. **What is "ground," in your own words?** *Draft answer:* Ground is the point I choose as the 0 V reference so single-node "voltages" mean something — since voltage only exists *between* two points, every node voltage is really "this node measured against ground." It's a bookkeeping choice (SPICE's node 0), and often also the common return path of the circuit.

## Falstad labs (Ch. 1–2 builds)

- [ ] Battery + single resistor: verify I = E/R by hovering the wire; verify wire drops ≈0 V between common points
- [ ] The three worked examples (12 V/3 Ω, 36 V/9 Ω, 7 Ω/2 A) — predict on paper first
- [ ] Double the source voltage on a fixed R → confirm current ×2 and power ×4
- [ ] Break the loop → confirm current = 0 everywhere and full source V appears across the gap
- [ ] Series loop + parallel pair for the deliverable: predict each branch current by hand, then hover and check

**Ch. 5–6 builds:**

- [ ] Series 9 V + 3k/10k/5k: fill the whole E/I/R table on paper first (18k → 500 µA → 1.5/5/2.5 V), then hover-verify every value
- [ ] Parallel 9 V + 10k/2k/1k: same drill (0.9/4.5/9 mA → 14.4 mA → 625 Ω); confirm R_T came out *below* the smallest branch
- [ ] Failure sims — series circuit: short R2 (watch survivors' drops rise, shorted part at 0 V), then open R2 (current 0 everywhere, full supply across the gap)
- [ ] Failure sim — parallel circuit: open one branch, confirm the other branches don't change at all
- [ ] KVL walk: 45 V + 5k/10k/7.5k — step a voltmeter around the loop with consistent lead orientation, tally +45 −10 −20 −15 = 0; then walk the reverse direction and confirm it still sums to 0
- [ ] Current divider: 6 V + 1k∥3k∥2k — predict 6/2/3 mA with I_n = I_T·(R_T/Rn) first, verify by hover; then check KCL at one node by hand
- [ ] Power cross-check: add P = I·E per resistor in one of the above and confirm ΣP = P_source

## Hooks to later weeks

- Voltage-divides-by-resistance (§2.7 + 1.6) → **Week 2** divider derivation Vout = Vin·R₂/(R₁+R₂)
- Resistor power ratings → **Week 2** "when a ¼ W resistor smokes"
- Electrically-common troubleshooting (0 V between common points) → **Week 3** multimeter + continuity work
- Diode as one-way valve → **Week 9** flyback diode across the motor
- Nodes/netlists → **Week 20** KiCad nets
- Filament nonlinearity (R vs. temperature) → general datasheet skepticism: "R" is conditional
- Divider formula + loaded-divider sag → **Week 2** derivation self-check and the 3.3 V-from-5 V lab
- Pot as variable divider → **Week 3** build #4 (sweep + measure) and **Week 7** pot→ADC→PWM
- Pull-up/pull-down = a divider where one "resistor" is the switch → **Week 3** build #3, **Week 4** floating inputs, **Week 11** I2C pull-ups
- Failure signatures (full V across an open; 0 V across a short) → **Week 3** continuity/meter work, **Week 24** board bring-up debugging
- Meter shunt (current divider in your DMM) → **Week 19** burden voltage tile
- Breadboard column-of-5 internals + split rails + <1 A limit → **Week 3**; soldering & terminal strips → **Week 4**
- Common-wire numbering / TB labels → **Week 20** KiCad nets and schematic-as-map discipline
- Table method (Ohm vertical, rules horizontal) → the standing habit for every analysis chapter from here on
