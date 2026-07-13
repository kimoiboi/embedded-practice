# Week 1 Notes — DC Theory Foundations
**Source:** All About Circuits, Vol. I — Ch. 1 (Basic Concepts of Electricity), Ch. 2 (Ohm's Law), Ch. 3 (Electrical Safety), Ch. 4 (Scientific Notation & Metric Prefixes), Ch. 5 (Series & Parallel Circuits), Ch. 6 (Divider Circuits & Kirchhoff's Laws), Ch. 7 (Series-Parallel Combination Circuits)
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
- SPICE prints results like `-4.800E+00` — that's E-notation, decoded properly in §4.6.

---

## Chapter 3 — Electrical Safety

**Why this chapter is in a CS→embedded plan:** almost everything on the roadmap runs at 3.3–5 V from USB — genuinely safe territory. The danger lives at the edges: the mains side of wall adapters and the soldering iron (Week 4), anything opened up that has a plug, and the ebike pack / power station (36–48 V with serious current capability — over the danger line defined below). Bonus: every safety rule here is just Ch. 1–2 circuit analysis with stakes, so this doubles as review.

### 3.2 What current does to a body — three failure modes

1. **Burns.** The body has resistance; current through it dissipates P = I²R as heat — and unlike a flame, electricity cooks *from the inside*: organs and tissue beneath unbroken skin.
2. **Tetanus** — involuntary, sustained muscle contraction. Nerves signal electrochemically with tiny voltages and currents; an external shock current overwhelms the channel, and every muscle in the path locks up. The finger-*bending* (flexor) muscles are stronger than the finger-*extending* ones, so a hand around a live conductor clamps **on** — "froze on the circuit" — which maintains contact and makes everything worse. Only stopping the current releases the grip.
3. **Fibrillation.** The diaphragm and heart are muscles too. Currents even *below* the tetanus threshold can scramble the heart's pacemaker signals → it flutters uselessly instead of pumping → asphyxiation / cardiac arrest.

**AC vs. DC — they fail differently:**

| | 50/60 Hz AC (mains) | DC |
|---|---|---|
| muscle effect | sustained tetany — freezes you **onto** the source, prolonging exposure | single convulsive contraction — often throws you **off** |
| heart effect | fibrillation (flutter; doesn't self-recover) | tends to stop the heart still — better recovery odds once current stops |
| relative danger | **3–5× worse** than DC at the same voltage/current | baseline |

- Defibrillators exploit exactly this: a jolt of **DC** halts fibrillation so the heart can restart in a normal rhythm. (Fibrillating heart ≈ livelocked process; the defib is a hard reset.)

### 3.3 Shock requires a complete circuit — the two-contact-point rule

- Ch. 1's break-location rule, applied to you: current needs a closed loop, so **no shock without two contact points on the body**. The famous bird on the power line: both feet on the *same* conductor → electrically common (§2.7) → 0 V between them → no current through bird.
- You are not the bird because you **stand on the earth**, and power systems deliberately ground one conductor. Touch just the hot wire and the loop closes anyway: wire → you → dirt → grounding rod → back to the source.
- **Why ground the system at all, if that's what creates the path?** Because grounding one side *guarantees that side is safe to touch* (0 V to earth). An ungrounded system seems safer but is actually **unpredictable**: any accidental **ground fault** — tree branch on a wire, dirty rain-wet insulators, groundwater into a buried cable — silently grounds one conductor, and you have no idea which wire just became the deadly one. Worse: two people touching different conductors complete the circuit *through each other* via the earth. Deliberate grounding buys certainty.
- Footwear is not PPE: ordinary soles are thin, the wrong material, and compromised by moisture and sweat salts. Book figures: rubber ≈ 20 MΩ; dry leather 100–500 kΩ; **wet leather 5–20 kΩ**.
- Dirt conducts poorly — but "poorly" is irrelevant when milliamps injure and the system pushes with kilovolts. Concrete conducts fairly well (intrinsic water + electrolytes); asphalt (oil-based) insulates much better.

### 3.4 Ohm's Law with stakes — I = E/R, where R is *you*

- "It's current that kills, not voltage" is only half-true. Current does the damage, but **I = E / R_body**: voltage supplies the push and your body-plus-contact resistance sets how much actually flows. All three variables matter.
- **Body resistance is a variable, not a constant** (echo of the nonlinear filament, §2.6):

| condition (hand-to-hand) | R ≈ |
|---|---|
| clean dry skin, light finger contact | ~1 MΩ |
| sweaty fingers on a wire | ~17 kΩ |
| sweaty, solid grip on metal (ring, pipe, tool) | ~1 kΩ |

- The chapter's worked math — voltage needed to push 20 mA (can't-let-go territory): 1 MΩ → 20 kV. 17 kΩ → 340 V. 1 kΩ → **20 V**. Read that last row twice.
- ⚠️ **Industry rule: treat anything above 30 V as dangerous** — because worst-case body R makes tens of volts sufficient. *The ebike pack and the power station live above this line*, with current capability to spare. Handle them with mains-level respect: dry hands, one hand, no jewelry.
- Nasty positive-feedback loop: shock → sweating + tetanus-tightened grip → contact R drops → current rises → worse. A survivable shock can *escalate while it's happening*.
- The danger ladder (60 Hz AC — the worst case; DC thresholds run several times higher):
  - ~1 mA: threshold of perception
  - ~6–9 mA: painful, muscle control retained
  - **~10–16 mA: painful, can't let go**
  - ~15–23 mA: severe pain, breathing difficulty
  - ~100 mA (suggested as low as ~17 mA across the chest): fibrillation possible
- Calibration for intuition: the classic LED operating current — 20 mA — is already inside the can't-let-go band. Milliamps through the chest are the entire game.
- Contact area is parallel resistance (§5.3 preview): two hands on a pipe = exactly **half** the R of one hand (two parallel entry paths). Metal jewelry = an excellent low-R contact point, and a burn hazard even at "safe" voltages — rings bridging low-voltage/high-current points cook fingers.
- **The one-hand rule:** on any live circuit, work with one hand, the other in your pocket — it keeps the current path off the hand-to-hand route through heart and lungs (the worst possible path). Right hand conventionally preferred (heart sits left of center), but coordination beats convention.
- Low voltage harms indirectly too: a 12 V tingle that makes you flinch can throw your arm into a fan or drop a wrench across battery terminals (the author's own car anecdote — sweaty leg on chrome bumper).
- Insulated tools, gloves, and boots = deliberately added **series resistance** in the fault path (§5.2: series resistances add, so total current falls).

### 3.5 Safe practices — Zero Energy State and lock-out/tag-out

- **Zero Energy State** = *all* stored potential energy removed before work begins: voltage, spring tension, hydraulic/pneumatic pressure, suspended weight, chemical. Voltage *is* potential energy — a connected supply (or a charged capacitor) is fully dangerous while sitting there "doing nothing."
- The **disconnect switch** is a dedicated isolation device, separate from the everyday on/off switch, placed in the hot conductor. Open = full source voltage sits across the switch gap, 0 V at the load (Ch. 1's "full voltage across the break," used on purpose).
- Belt-and-suspenders: temporarily short/ground **both** sides of the load being serviced → 0 V across it guaranteed; if someone closes the disconnect anyway, the short trips the breaker instantly. (⚠️ Perspective check: breakers and fuses exist to keep **wires** from overheating — protecting people is *not* their job; the shorting-wire trick merely hijacks them for it.)
- **Lock-out/tag-out (LOTO):** every worker hangs their *own* padlock on every relevant energy disconnect, plus a signed tag (who, what, how long). Power cannot return until *every last lock* is removed — each worker holds a veto. CS mapping: it's a reference count on de-energization; the system re-energizes only at count zero, and you may only release your own lock. Even so — never assume everyone followed procedure.
- **Check–use–check** the meter: (1) verify the meter reads a known-live source, (2) test the locked-out circuit, (3) verify the meter on the known source *again*. This guards against a broken meter reporting "dead" — a false negative from a single unverified sensor on a life-critical check nearly killed the author once. Redundancy for safety-critical reads, always.
- Very last step before touching: brush the conductor with the **back of the hand** first — if voltage remains, the clench reflex pulls the fingers *away from* the conductor instead of around it. A final fallback layer, never a substitute for the meter checks.

### 3.6 Emergency response

- Victim frozen or unconscious on a circuit: **kill the power first** (disconnect/breaker). Grab them and there may be enough voltage across their body to freeze you in the same circuit — two victims. The chapter's line: don't be a hero; electrons don't respect heroism.
- Can't locate the disconnect fast enough: pry or knock them clear with something *dry and nonconductive* — wooden board, nonmetallic conduit — or loop an extension cord around the torso and pull. Expect their grip to be locked (tetanus).
- Once clear: breathing and pulse first; CPR if trained, and keep going until relieved by qualified personnel. Conscious victim: keep them lying still, warm, and comfortable (risk of physiological shock — a circulation problem, different thing from electric shock).
- ⚠️ **The danger doesn't end at the incident:** shock can trigger heart irregularities or a heart attack **hours later**. Victims need monitoring even if they feel fine.

### 3.7 Everyday hazard sources

- Wet skin = resistance collapse, and salty sweat is worse than fresh water. Bathrooms and pools are the classic appliance-shock venues — keep powered gadgets away from water, period. Surprise entry: landline phone wiring idles at 48 V DC and hits **~150 V AC while ringing** — well over the 30 V line.
- "It's battery-powered so it's safe" is false: devices with **voltage-boosting circuitry** (boost converters, flash-charge circuits) can hold lethal internal potentials off a few AA cells.
- Damaged extension cords and tools that occasionally tingle: out of service *immediately*. Decommissioning trick: unplug it and **cut off the male plug** so nobody can use it before it's repaired.
- **Downed power lines — step potential:** current fans out through the earth between the fallen conductor and the system ground point, dropping substantial voltage along the ground itself. Feet planted a stride apart = two taps on a voltage divider made of dirt → shock up one leg and down the other *without touching anything*. If a line drops near you: run (only one foot down at a time) or stand on one foot.

### 3.8 Safe circuit design — hot, neutral, ground, GFCI

- Two-wire household power: the grounded conductor is the **neutral** (held at earth potential); the ungrounded one is the **hot** (the dangerous one). Grounding exists *purely for people* — the load runs identically without it.
- Failure model to reason from: an internal wire contacts a metal appliance case.
  - neutral → case: nothing happens (case was already ≈ earth potential)
  - **hot → case: the case is now live**, and the user touching it becomes the ground path.
- The defense-in-depth stack (each layer independent):
  1. **Polarized plugs** — mechanical keying (one wide prong) so the designer *knows* which internal conductor is hot and routes it away from the case. Defeated if the plug is reversible.
  2. **Double insulation** — nonconductive case = a second, independent insulation layer.
  3. **Three-prong grounded case** — the case is hard-wired to earth; a hot→case fault becomes a dead short that trips the breaker instantly, and the case never rises above earth potential. ⚠️ Never snip the third prong to fit a two-slot receptacle — that deletes the entire safety mechanism while the appliance keeps working normally (silent failure).
  4. **GFCI** (RCD/ELCB outside North America) — continuously compares I_hot against I_neutral. In a healthy appliance they're identical (one loop, §1.4). Any imbalance means current is leaking out via some other path — possibly a person — so it trips within milliseconds. This is **KCL deployed as a runtime safety check**: current in must equal current out; a mismatch is an invariant violation → kill the power. Works regardless of the appliance's own design, which is why wet locations require them.
- **AFCI** — an electronic breaker that recognizes the signature of intermittent *arcing* (repetitive high-current spikes whose average never trips a thermal breaker but which start fires). Fire protection, **not** shock protection — bedrooms get AFCIs, kitchens/baths still need GFCIs. Known to nuisance-trip on brushed-motor startup.

### 3.9 Safe meter usage — the multimeter's contract

The practical payoff — Week 3's meter work runs on these rules. A multimeter has three personalities, and mixing them up is the main way meters hurt people and die.

- **Voltmeter (V):** connect *across* two points — in **parallel** — because voltage only exists between two points (§1.4). Input resistance ≈ many MΩ, so it draws essentially nothing and doesn't disturb the circuit. Cautions: never let the probe tips touch each other on a live circuit (instant short/arc), hand-to-hand probing of a high-voltage circuit is itself a hazard (latch one probe with a spring clip and work one-handed where possible), and cracked probe insulation = fingers on conductors — never improvise DIY probes.
- **Proving a circuit dead** (the LOTO verification step): a meter set to AC reads 0 on DC and vice versa, so check **both modes**; and check **all pairs** — every conductor-to-conductor pair *and* every conductor-to-ground. Three wires = 6 pairs × 2 modes = **12 checks**. Then re-verify the meter on a live source (check–use–check).
- **Ohmmeter (Ω):** the meter *sources* a small current from its internal battery and measures how hard pushing it is. Therefore **de-energized circuits only** — any external voltage corrupts the reading at best and damages the meter at worst. Continuity readings: ≈0 Ω = connected; "O.L." (open loop) = broken path. (This is the §2.7 troubleshooting tool: two points that should be common must read ≈0 Ω.)
- **Ammeter (A) — the trap mode:**
  - Current is measured *through*, so the meter goes **in series**: physically break the circuit and route the current through the meter.
  - In A mode the meter is ≈0 Ω *by design* — added resistance would change the very current being measured.
  - ⚠️ **The classic blunder:** finish a current measurement, spin the dial back to V, but leave the red lead in the A socket, then probe across a source. You've just connected a ≈0 Ω path straight across the supply — a dead short *through the meter*. Sparks, blown fuse, possibly a dead meter. Most meters beep at the lead/dial mismatch; don't outsource thinking to the beep.
- One-liner to memorize: **voltmeter ≈ ∞ Ω, wired in parallel; ammeter ≈ 0 Ω, wired in series — and each is a catastrophe in the other's position.**
- The internal **fuse** (which blows on ammeter abuse) protects *the meter*, only incidentally you. Self-test it in Ω mode probing between the two red sockets: low ohms = good fuse, O.L. = blown.

### 3.10 Where the numbers came from

- The threshold tables trace to Charles Dalziel's UC Berkeley experiments (volunteers gripping a wire and a brass plate at increasing current until release became impossible). Sources (MIT vs. Bussmann) disagree slightly; the book lists the *lowest* figures. Treat every threshold as approximate and person-dependent — the engineering takeaway is simply: **double-digit milliamps are already dangerous.**

---

## Chapter 4 — Scientific Notation and Metric Prefixes

Short chapter, permanent skill: this is the **number-formatting layer** of electronics. Every datasheet, schematic, silkscreen, and simulator speaks it — the goal is fluency, not familiarity.

### 4.1 Scientific notation and significant digits

- Electronics spans absurd ranges: 1 A = 6.25 × 10¹⁸ electrons/second (Ch. 1's coulomb again); a proton masses 1.67 × 10⁻²⁴ g. Long strings of zeros invite transcription errors and bury what matters.
- **Significant digits encode measurement *precision*, not just value.** "The car weighs 3,000 lbs" (rounded) → one sig fig; "3,005 lbs" → four, because those middle zeros were clearly measured, not placeholders. Plain decimal notation *cannot express* "3000, exact to the pound" — scientific notation can: **3.000 × 10³** (zeros after the decimal are never placeholders, so writing them asserts they're significant).
- Format: mantissa in [1, 10) × 10^exponent. Positive exponent → slide the decimal right (big numbers); negative → left (small numbers).
- CS anchor: this is IEEE-754 in base 10 — sign, significand, exponent. You've read `6.25e18` your whole programming life; this chapter is just the pencil-and-paper version.

### 4.2 Arithmetic with scientific notation

- **Multiply:** multiply the mantissas, **add** the exponents. **Divide:** divide the mantissas, **subtract** the exponents. (Identical exponent rules to your powers-of-2 arithmetic — 2⁵·2³ = 2⁸ reasoning, base 10.)
- Renormalize afterwards: (6.25 × 10¹⁸)(3.6 × 10³) = 22.5 × 10²¹ → **2.25 × 10²²**.
- Historical why: slide-rule users did mantissas on the rule and exponents in their heads. The tooling is obsolete; the skill survives as **instant order-of-magnitude sanity checking** — the fastest bug detector for hand calculations there is.

### 4.3 Metric (engineering) notation

- Metric prefixes = scientific notation with the power-of-ten swapped for a letter, exponents restricted to **multiples of 3**, and the mantissa allowed to roam 1–999.

| prefix | symbol | power | | prefix | symbol | power |
|---|---|---|---|---|---|---|
| tera | T | 10¹² | | milli | m | 10⁻³ |
| giga | G | 10⁹ | | micro | µ | 10⁻⁶ |
| mega | M | 10⁶ | | nano | n | 10⁻⁹ |
| kilo | k | 10³ | | pico | p | 10⁻¹² |

  (Extremes exist — P/E/Z/Y going up, f/a/z/y going down — plus non-multiple-of-3 stragglers hecto/deca/deci/centi that electronics ignores.)
- ⚠️ **Case is load-bearing: M = mega, m = milli — nine orders of magnitude apart.** mW vs. MW is *the* classic units typo. Also unlearn the CS reflex: in electronics **k = exactly 1000, never 1024** — no KiB ambiguity here.
- Embedded life happens in a narrow prefix band; get fast in it: kΩ/MΩ resistors, µF–nF–pF capacitors, mA run currents and **µA sleep currents** (the number battery-powered firmware lives and dies by), MHz clocks, **ns** rise/setup times, mV noise margins.
- **The "4k7" convention:** decimal points vanish in cheap print and tiny silkscreens (4.7 k misread as 47 k), so the prefix letter replaces the point: 4.7 kΩ → **4k7**, 2.2 Ω → **2R2**, 0.267 m → 0m267. You'll see this constantly on real PCBs and schematics — it's a feature, not a typo.

### 4.4 Prefix conversions

- Conversion = sliding the decimal along the prefix number line: count the powers of ten between source and target prefix, shift the decimal that many places in that direction.
- Worked: 0.000023 A → µA: unit→micro is 6 steps right → **23 µA**. 304,212 V → kV: 3 left → **304.212 kV**. 50.3 MΩ → mΩ: mega→milli is 9 right → **50.3 × 10⁹ mΩ**.
- Sanity invariant: **bigger prefix ⇔ smaller mantissa** (and vice versa) — the physical quantity is conserved, only the representation moves. If both grew, you shifted the wrong way. Same instinct as byte↔KB↔MB conversions.
- (A number with no visible decimal point has one implied after its last digit: 436 = 436.)

### 4.5 Calculator use

- The **[EE]/[EXP]** key enters powers of ten directly; **[+/−]** negates whichever part was just typed — order matters: −3.221 × 10⁻¹⁵ is `3.221 [+/-] [EE] 15 [+/-]` (first one flips the mantissa, second flips the exponent).
- Display modes: **SCI** normalizes the mantissa to 1–10; **ENG** forces the exponent to a multiple of 3 — i.e., prefix-ready output. **Set the calculator to ENG and leave it there** — it then speaks datasheet natively, and every result maps straight onto a prefix from the table above.

### 4.6 SPICE and E-notation

- Simulators — and every programming language — print **E-notation**: `-4.800E-03` = −4.8 × 10⁻³ A = **−4.8 mA**. It's `printf("%e")`; already fluent.
- Netlists accept prefixes inline: `r1 1 0 5k` means 5 kΩ. And output convention: `1.15E-01` W gets expressed as **115 mW**, because electronics sticks to multiple-of-3 prefixes (nobody says "1.15 deciwatts").
- ⚠️ *Plan-note (gap-filler beyond the chapter):* SPICE-family netlist tools are **case-insensitive**, so `M` cannot mean mega — `1M` parses as 1 *milli*; mega is spelled **`MEG`**. A classic silent simulation bug. Falstad's GUI spares you; ngspice/LTspice netlists won't.
- SPICE's negative sign on source current is a tool convention, not physics — the same lesson as KVL's negative answers in §6.2: **a sign is direction bookkeeping against an assumed orientation**, nothing more.

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
- This section only handles pure-series and pure-parallel faults; **§7.4** scales the same reasoning to combination circuits using symbolic {↑, ↓, same} tables.

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

## Chapter 7 — Series-Parallel Combination Circuits

*The payoff chapter. Real circuits are almost never purely series or purely parallel — a pull-up + button + GPIO pin, a divider feeding an ADC, an LED bank off one rail: all hybrids. This chapter is the general algorithm for taming any resistive circuit, and it's secretly a chapter about recursion.*

### 7.1 What a series-parallel circuit is — and why the Ch. 5 rules stop applying globally

- **Series-parallel** = a circuit that is series in some places and parallel in others. Diagnostic: more than one current path (→ not series), *and* more than two sets of electrically common points (→ not parallel).
- **The reference circuit for the whole chapter:** 24 V source driving (R1 = 100 Ω ∥ R2 = 250 Ω) in series with (R3 = 350 Ω ∥ R4 = 200 Ω). Current leaves the battery, splits through R3/R4, rejoins, splits again through R1/R2, rejoins home.
- ⚠️ **No rule applies "across the table" anymore.** You can't sum all four R's (they're not all in series) and can't reciprocal-sum them (not all in parallel). The six Ch. 5 rules still hold — but only **locally**, inside each pure-series or pure-parallel subsection. The new skill is *scoping*: knowing which rule is legal where.
- CS anchor: the series/parallel rules just became **block-scoped variables** — perfectly valid inside their cluster, meaningless at global scope.
- Ohm's Law is unaffected: it never cared about topology, only about one component's (or one equivalent's) own E/I/R — vertical columns in the table, exactly as before.

### 7.2 The analysis algorithm — reduce, solve, expand

The book lists 8 steps; they compress to three phases:

1. **REDUCE** — find any pure-series or pure-parallel cluster, replace it with a single equivalent resistor, re-draw (and give the equivalent its own table column). Repeat until one resistor remains.
2. **SOLVE** — I_T = E_T / R_T on that final resistor.
3. **EXPAND** — un-collapse one reduction at a time, pushing knowns back down: a **series equivalent hands its current to its members** (series: same I), a **parallel equivalent hands its voltage to its members** (parallel: same E). Ohm's Law fills in the missing partner at every level. Finish with P = I·E per component.

- **Notation to adopt (the book's own):** `R1//R2` = R1 in parallel with R2; `R1--R2` = in series. The reference circuit collapses to **R_T = (R1//R2)--(R3//R4)**.
- CS anchor — that expression is an **AST**. `//` and `--` are binary operators over resistances. **Reduce = post-order evaluation** of the tree (children first, bottom-up). **Expand = walking back down**, distributing values by node type: at a `--` node, copy I to both children; at a `//` node, copy E to both children. The extra table columns (R1//R2, R3//R4) are literally the stack frames. Divide-and-conquer, nothing more.

**Worked — the reference circuit (rebuild in Falstad, verify every cell):**

| stage | operation | result |
|---|---|---|
| reduce | R1//R2 = (100·250)/(100+250) | **71.429 Ω** |
| reduce | R3//R4 = (350·200)/(350+200) | **127.27 Ω** |
| reduce | R_T = 71.429 + 127.27 (series) | **198.70 Ω** |
| solve | I_T = 24 / 198.70 | **120.78 mA** |
| expand (series step) | both equivalents carry I_T → E = I·R | E(R1//R2) = **8.6275 V**, E(R3//R4) = **15.373 V** |
| expand (parallel step) | members inherit their equivalent's voltage → I = E/R | I₁ = **86.28 mA**, I₂ = **34.51 mA**, I₃ = **43.92 mA**, I₄ = **76.86 mA** |

- **Free built-in checks — run them every time:** KVL: 8.6275 + 15.373 = 24 ✓. KCL: 86.28 m + 34.51 m ≈ 120.78 mA ✓ and 43.92 m + 76.86 m = 120.78 mA ✓. If either fails, a mistake exists, guaranteed (§5.5's power-sum check works too).
- The chapter cross-verifies with SPICE, inserting **0 V "dummy" sources** in series with each resistor — SPICE can only report current *through voltage sources*, so zero-volt sources act as free ammeters. (Falstad's hover spares you the trick, but you'll meet it again in ngspice/LTspice netlists.)
- ⚠️ Don't be intimidated by "71.429 Ω": that precision is pedagogy, not practice. Real parts are ±5% or ±1% (see the playbook below) — carry 3–4 sig figs through the math and remember the components are fuzzier than your arithmetic (§4.1's precision lesson).

### 7.3 Re-drawing convoluted schematics — normalizing the graph

Real schematics (and sketches traced off physical boards) don't arrive pre-organized. The fix is a mechanical **re-drawing algorithm**:

1. Trace one loop from battery − terminal around to +, following the components nearest the battery, ignoring everything else. **Mark voltage-drop polarity on each resistor as you pass** (electron flow: enters −, exits +).
2. Draw that loop as a clean vertical schematic.
3. Find a loop that wraps *around* an already-traced component; trace it, mark polarities (they'll mirror the component it parallels), add it to the vertical drawing alongside its partner.
4. Repeat step 3 until every component is placed.

- Why this is legal: **wire length and routing don't matter — only connection topology does** (§2.7's electrically-common idea doing the heavy lifting). Stretch, shrink, bend at will; the circuit is unchanged.
- CS anchor: a circuit is a **graph**, and any particular schematic is just one drawing (embedding) of that graph. Re-drawing = a behavior-preserving refactor into canonical, readable form. An ugly schematic is spaghetti code: identical semantics, hostile layout.
- The chapter's 7-resistor monster, once re-drawn, reduces mechanically right-to-left: R2//R3 → (--R4) → (//R5) → (--R7) → (//R6) → (--R1) = R_T. Each step is one AST node collapsing.
- The polarity marks aren't busywork: they're the correctness guide when placing paralleled components (+ joins +, − joins −), and they're KVL sign discipline (§6.2) getting drilled early.

### 7.4 Component failure analysis — qualitative reasoning at full scale

> Dirac: "I understand an equation when I can predict the properties of its solutions without actually solving it." The circuit version: predicting a fault's effects with **zero arithmetic**.

- Method: run the exact same table algorithm, but over **symbols {↑, ↓, same} instead of numbers**. Fill in givens first (the failed part gets an arrow — shorted = R↓, open = R↑ — everything else "same"), then propagate: Ohm's Law vertically, series/parallel rules horizontally. Same machine, abstract inputs.
- CS anchor: this is **sign/monotonicity analysis** — evaluating the program over the abstract domain {↑, ↓, same} instead of concrete values (the textbook first example of abstract interpretation). Faster than arithmetic, and immune to keystroke errors.
- Worked scenario (R2 fails **shorted** in the reference circuit): R2↓ → R1//R2 ↓ → R_T ↓ (single-component rule, below) → I_T ↑ (I = E/R, E same, R↓) → that current flows through both series sections → E across R3//R4 ↑ (E = IR, R same, I↑) → E across R1//R2 ↓ (KVL: the two drops still sum to a fixed 24 V) → parallel members inherit their section's arrow → branch currents by I = E/R where decidable...
- ⚠️ **The two-moving-inputs trap:** when *both* inputs of an Ohm's-Law equation carry arrows in conflicting directions (R1//R2 has R↓ *and* I↑ — does E go up or down?), **Ohm's Law is undecidable** — the answer depends on magnitudes you deliberately don't have. Switch tools: some horizontal rule can always break the tie. Here, KVL decides E(R1//R2)↓ (the other drop rose, total is fixed). Later, I through R2 (E↓ *and* R↓, ambiguous) is decided by KCL (section current ↑ while I through R1 ↓ ⇒ I through R2 must be ↑). **Knowing which rule is decidable is the actual skill.**
- **The three fault rules to memorize:**
  1. A single failed component moves **total resistance in the same direction** as its own change. (Magnitude differs; direction always matches.)
  2. **Shorted:** its R ↓ (≈0 Ω), current *through* it ↑, voltage *across* it typically ↓ — exception: an ideal source wired directly across it pins the voltage.
  3. **Open:** its R ↑ (≈∞), current through it → **0** (no continuity), voltage across it typically ↑ — up to the **full source voltage** (§5.7's troubleshooting gold, still true in hybrids).
- Field direction is the inverse function: the book predicts *symptoms from a known fault*; debugging a board is inferring *the fault from observed symptoms*. Fluency forward makes the inverse tractable — the same reason you can't debug code without knowing what correct execution looks like.

### 7.5 Building series-parallel circuits — layout is for humans

- Breadboard: arrange parts to **mirror the schematic** where possible — free comprehension at zero electrical cost.
- Need 24 V but own 6 V batteries? **Sources stack in series**: four 6 V in series = 24 V. (Same series voltage rule, applied to sources — this is also exactly how your ebike's battery pack works internally: series groups of cells.)
- **Terminal strips:** components physically can't sit like the drawing, so the builder "bends" the schematic mentally. Method: mount and label all resistors first, then add wires **one schematic-connection at a time, overdrawing each connection on the schematic as it's completed** — mark-and-sweep for wiring; nothing gets skipped or doubled.
- **Etiquette rules, with reasons:**
  - ⚠️ **Max two wire ends per screw terminal.** Three works electrically but stresses the screw and makes a mess for whoever services it (a "faux pas," per the book). If a third connection is needed, land it on a different terminal that's already electrically common.
  - **Orient components so all voltage-drop polarities read the same direction.** Electrons don't care; the human with an analog voltmeter (which pegs backwards on reversed polarity) very much does.
- The chapter's closing law, worth engraving: **whenever a design can be modified for easier comprehension or maintenance at zero functional cost — do it.** The "human factor." This is code-review energy: the next person to probe the board is future-you at 1 a.m.

---

## Week 1 map — all seven chapters in one place

*(One consolidated summary block, per plan: each entry = core idea → the one thing never to forget.)*

**Ch. 1 — Basic concepts.** Electricity is mobile electrons. Voltage = stored push *between two points*; current = coordinated flow *through* a loop; resistance = opposition that converts flow to heat. Never forget: voltage is always between two points, current is identical everywhere in a single loop, and a break anywhere stops flow everywhere — with the **full source voltage appearing across the break**.

**Ch. 2 — Ohm's Law & power.** E = I·R relates the big three; P = I·E (and I²R, E²/R) measures work-rate. Resistors carry two independent ratings: ohms *and* watts. Never forget: **every quantity in one equation must refer to the same two points**, and doubling voltage quadruples power (the square).

**Ch. 3 — Safety.** Current does the harm; voltage pushes it; body resistance is a *variable* (≈1 MΩ dry → ≈1 kΩ sweaty metal grip). Never forget: treat **>30 V as dangerous**, double-digit mA are already dangerous, Ω-mode on dead circuits only, and the red-lead-left-in-the-A-socket blunder is a dead short through the meter.

**Ch. 4 — Notation.** Scientific notation + metric prefixes are the number system of electronics; ENG calculator mode speaks it natively. Never forget: **M ≠ m** (nine orders of magnitude), k = 1000 never 1024, and 4k7 = 4.7 kΩ.

**Ch. 5 — Series & parallel.** Series (one path): same I, R's add, drops add. Parallel (same two node-sets): same E, branch I's add, R_T lands *below the smallest branch*. Never forget: **the table method** — Ohm's Law vertically, topology rules horizontally — and the failure signatures: full V across an open, ≈0 V across a short.

**Ch. 6 — Dividers & Kirchhoff.** Series divides voltage by resistance ratio: E_n = E_T·(Rn/R_T). Parallel divides current inversely: I_n = I_T·(R_T/Rn). Divider fractions are always < 1 — if yours isn't, it's flipped. KVL: loop voltages sum to zero; KCL: node currents sum to zero. Never forget: **signs are direction bookkeeping** against your assumed meter orientation, nothing more.

**Ch. 7 — Series-parallel.** No global rules; instead **reduce → solve → expand**. Collapse pure clusters into equivalents — (R1//R2)--(R3//R4) — down to one resistor, get I_T, then unwind: series equivalents pass their *current* down, parallel equivalents pass their *voltage* down, Ohm's Law fills the gaps, KVL/KCL cross-check for free. For faults, run the same table over {↑, ↓, same}. Never forget: **when Ohm's Law has two moving inputs it's undecidable — a series/parallel rule breaks the tie**; and topology confusion, not formula confusion, is what actually causes wrong answers.

---

## The practical playbook — picking resistors and choosing formulas

*(Plan-note, gap-filler beyond the book: the "okay, but how do I actually USE this at a bench" section. This is the bridge from Vol. I theory to the Arduino/STM32 work.)*

### The universal design loop — nearly every resistor you'll ever choose

1. **Identify the constraint.** Almost always either a target *current* (LED brightness, max GPIO pin current) or a target *voltage* (divider output, reference level).
2. **Ohm's Law for the value:** R = E/I — where E is the voltage **the resistor itself sees** (not necessarily the supply!) and I the current through it. Getting E wrong here is the #1 beginner error, and it's the same-two-points rule from §5.6 again.
3. **Power check:** P = I²R (or E²/R). Buy a part rated **≥ 2× the dissipation** — the standing derating habit. Your ¼ W kit parts are fine below ~125 mW, which covers nearly everything at logic voltages.
4. **Round to a standard value** (next section — usually round *up* for current-limiting: higher R = less current = safer) and **re-run steps 2–3 with the real value** to confirm you're still in spec.

### Standard values — why every circuit on Earth contains a 330 Ω and a 4.7 k

- You can't buy arbitrary ohms. Resistors come in **E-series** preferred values, spaced *logarithmically* so adjacent values' tolerance bands just touch — no gaps, no pointless overlap:
  - **E12 (±10% spacing):** 10 · 12 · 15 · 18 · 22 · 27 · 33 · 39 · 47 · 56 · 68 · 82 — times any power of ten.
  - **E24 (±5%)** interleaves the rest: 11, 13, 16, 20, 24, 30, 36, 43, 51, 62, 75, 91.
- So "my math says 300 Ω" becomes **330 Ω** off the shelf, and 4,700 Ω is a first-class citizen (47 × 100) — that's why 4k7 shows up in every schematic ever drawn.
- CS anchor: E-series is logarithmic quantization — same reason float32 spacing grows with magnitude. Percentage error is what's held constant, not absolute error.
- ⚠️ **Tolerance eats false precision:** a ±5% "330 Ω" is legitimately anything from 313.5–346.5 Ω. Design so ±5% *doesn't matter* — for LEDs, pull-ups, and dividers feeding high-impedance inputs, it never does. When it genuinely matters (precision dividers, current-sense shunts), buy ±1% (E96) parts; never try to hand-select ±5% ones.

### Recipe 1 — the LED current-limiting resistor (the rite of passage)

Series chain: rail → R → LED → GND. The LED drops a roughly fixed **forward voltage V_f** (≈1.8–2.2 V red/yellow/green; ≈3.0–3.4 V blue/white — check the datasheet). **The resistor only gets what's left over** — that's the E in step 2:

**R = (V_rail − V_f) / I_target**

- 5 V rail, red LED (V_f ≈ 2 V), 10 mA target: R = 3 V / 10 mA = 300 Ω → standard **330 Ω** → actual I = 3/330 ≈ 9.1 mA. Perfectly fine — perceived LED brightness is roughly logarithmic; 9 vs 10 mA is invisible.
- Power check: P = I²R ≈ (9.1 m)² · 330 ≈ **27 mW** ≪ 250 mW ✓. LED resistors essentially never stress a ¼ W part at logic voltages.
- 3.3 V GPIO version: red V_f 1.8 V, 6 mA (gentle on the pin): R = 1.5/0.006 = 250 → **270 Ω**. ⚠️ **The MCU pin is a circuit component too** — check the datasheet's per-pin current limit (typically ~20 mA absolute max, less recommended, plus a *total-across-all-pins* budget).

### Recipe 2 — pull-up / pull-down sizing (Ch. 6's divider in disguise)

A pull-up + switch (or open-drain pin) is a two-leg voltage divider whose bottom leg is either ≈∞ Ω (switch open → pin reads ≈V_rail) or ≈0 Ω (closed → pin reads ≈0 V). Sizing is a **trade-off, not a formula**:

| | strong pull (1 k) | typical (10 k) | weak pull (100 k) |
|---|---|---|---|
| current burned while pulled low (5 V rail) | 5 mA — ouch | 0.5 mA | 50 µA |
| edge speed / noise immunity | fast, solid | fine for buttons | slow (RC against pin + wiring capacitance), noise-prone |

- **Defaults: 10 k** for GPIO buttons and reset lines; **4.7 k** for I2C at ordinary speeds (bus capacitance needs the stronger pull — the RC rise-time problem in the flesh); drift toward 47–100 k only when a µA sleep-current budget rules (§4.3's battery-firmware lesson meeting Ohm's Law).

### Recipe 3 — a voltage divider that survives its load (Ch. 6 + Ch. 7, combined)

Unloaded, pick the ratio: V_out = V_in · R₂/(R₁+R₂). But connect a load and it **parallels R₂** — the circuit is now series-parallel, and Ch. 7 is why you can compute the sag *exactly*: effective bottom leg = R₂//R_load < R₂, so the ratio (and V_out) drops.

- **Rule of thumb: divider current ≥ 10× the load current** (equivalently **R₂ ≤ R_load/10**) → sag stays under ~10%. Go 100× stiff for anything feeding an ADC reading you care about.
- The absolute scale is then a power trade: the divider burns V_in²/(R₁+R₂) **continuously**. 10k+10k across 5 V = 250 µA forever — irrelevant on USB power, fatal on a coin cell.
- ⚠️ **Dividers make references, not supplies.** Anything drawing real current gets a regulator. (Also the standing trick for reading the ebike pack's 36–48 V with a 3.3 V ADC — divide it down ~15:1, high-ohm, and mind §3's rules while probing it.)

### The dispatch table — which formula, when

| you know | you want | reach for |
|---|---|---|
| E across a component + its R | current through it | I = E/R |
| target I + the E the resistor will see | the resistor value to buy | R = E/I → round up to E12/E24 → re-check |
| any two of E, I, R **on the same component** | the third | Ohm's Law — always legal within one column |
| it's a series chain | anything | one shared I; R's add; drops add; drop ratio = resistance ratio (E_n = E_T·Rn/R_T) |
| it's a parallel bank | anything | one shared E; branch I's add; R_T = 1/Σ(1/R) (two resistors: product/sum) |
| it's a hybrid mess | anything | Ch. 7: reduce → solve → expand |
| a resistor about to be purchased | will it survive | P = I²R or E²/R → rating ≥ 2× |
| a fault, and no patience for arithmetic | expected symptoms | the {↑, ↓, same} qualitative table (§7.4) |

- **The meta-rule under all of it: identify the topology first** — series? parallel? hybrid (→ reduce)? Once topology is named, the correct formula picks itself. Nearly every "which formula do I use?" moment is actually unresolved topology, not missing math.

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

Prefixes:       T=10¹²  G=10⁹  M=10⁶  k=10³ | m=10⁻³  µ=10⁻⁶  n=10⁻⁹  p=10⁻¹²   (M ≠ m! k = 1000, not 1024)
Sci. notation:  multiply → add exponents · divide → subtract exponents · renormalize after
                bigger prefix ⇔ smaller mantissa (if both grew, you shifted the wrong way)

Safety:         treat > 30 V as dangerous · can't-let-go ≈ 10–16 mA (60 Hz AC) · fibrillation risk ≥ ~100 mA
                body R: ~1 MΩ dry → ~17 kΩ sweaty → ~1 kΩ metal grip;  I = E/R_body decides severity
Meter contract: voltmeter ≈ ∞ Ω, in parallel · ammeter ≈ 0 Ω, in series · Ω-mode on DEAD circuits only
                dead-check = both AC & DC modes, all conductor pairs + each-to-ground, check–use–check

Series-parallel: no global rules — REDUCE (collapse pure clusters → equivalents, repeat to one R)
                 → SOLVE (I_T = E_T/R_T) → EXPAND (series eq. passes I down · parallel eq. passes E down)
Notation:        R1//R2 = parallel equivalent · R1--R2 = series · e.g. R_T = (R1//R2)--(R3//R4)
Cross-checks:    section drops sum to E_T (KVL) · branch currents sum to section I (KCL) · ΣP = P_T
Fault rules:     R_T moves the SAME direction as the failed part
                 short → R↓, I(through)↑, E(across) usually ↓ · open → R↑, I(through)=0, up to full E across it
                 qualitative domain {↑, ↓, same} — Ohm's Law w/ two moving inputs is undecidable → use KVL/KCL/topology rule

Resistor picking: R = E_across/I_target → P = I²R, rate ≥ 2× → round to standard value → re-check
LED:             R = (V_rail − V_f)/I     (V_f ≈ 2 V red/yel/grn · ≈ 3.2 V blue/white — datasheet!)
Pull-up:         10k default GPIO · 4k7 I2C · 47–100k when µA sleep current rules (strong=fast+hungry, weak=slow+frugal)
Loaded divider:  bottom leg becomes R₂//R_load → keep R₂ ≤ R_load/10 (sag < ~10%) · dividers = references, not supplies
E12 decade:      10 12 15 18 22 27 33 39 47 56 68 82  (±5% band on "330 Ω" = 313.5–346.5 Ω — design so it doesn't matter)
```

## Week 1 self-check — worked

1. **Current through 220 Ω across 5 V?** I = E/R = 5/220 ≈ **22.7 mA** ✓ (this is *the* LED-resistor ballpark)
2. **Two 1 kΩ in parallel?** Equal resistors halve: **500 Ω**. (Ch. 5: R_T = 1/(1/R₁+1/R₂), or the two-resistor shortcut R₁R₂/(R₁+R₂) = 1M/2k = 500 Ω. Sanity check: below the smallest branch ✓.)
3. **What is "ground," in your own words?** *Draft answer:* Ground is the point I choose as the 0 V reference so single-node "voltages" mean something — since voltage only exists *between* two points, every node voltage is really "this node measured against ground." It's a bookkeeping choice (SPICE's node 0), and often also the common return path of the circuit.

**Ch. 3–4 additions:**

4. **Express 0.000047 F with a proper prefix.** Unit→micro is 6 places right → **47 µF** (the most common electrolytic cap value there is). Double-check via the invariant: prefix got bigger-in-smallness (µ), mantissa got bigger — one up, one down ✓.
5. **Period of a 16 MHz clock (the classic ATmega328 speed)?** T = 1/f = 1/(16 × 10⁶) = 0.0625 × 10⁻⁶ s = **62.5 ns**. Divide → subtract exponents, then slide to the nearest multiple-of-3 prefix. This one number is why AVR people count cycles at 62.5 ns each.
6. **If "current kills," why is the caution line drawn at 30 *volts*?** Because I = E/R_body and body R is a variable: sweat plus a solid metal grip drops it to ~1 kΩ, and 30 V / 1 kΩ = 30 mA — past can't-let-go, approaching heart-danger territory. The voltage threshold is just the current threshold with worst-case R plugged in. (Corollary: the 36–48 V ebike pack is over the line.)
7. **You measure current, then turn the dial to V and probe a battery — what happens if the red lead stayed in the A socket?** The meter is still ≈0 Ω internally in that socket, so you've shorted the battery through the meter: I = E/≈0 → huge current → blown meter fuse (best case). Verify the lead position *before* the dial, every time.

**Ch. 7 + playbook additions:**

8. **Reduce 10k--(10k//10k).** Equal pair in parallel halves → 5 k; series adds → **15 k**. (Two AST nodes, evaluated bottom-up.)
9. **Pick the resistor: 3.3 V rail, red LED with V_f = 1.8 V, target 6 mA.** The resistor sees 3.3 − 1.8 = 1.5 V (not 3.3 — same-two-points rule!). R = 1.5/0.006 = 250 Ω → standard **270 Ω** → actual I = 1.5/270 ≈ 5.6 mA ✓. Power: P = I²R ≈ 8.4 mW ≪ 250 mW ✓. Done in four steps of the design loop.
10. **Qualitative: in the reference circuit (24 V, (R1//R2)--(R3//R4)), R4 fails open — what happens to the voltage across R3?** R3//R4 collapses to just R3 → that section's R ↑ → R_T ↑ → I_T ↓ → drop across R1//R2 ↓ (same R, less I) → **by KVL, drop across R3 ↑**. Numbers to confirm the arrows: section R 127.27 → 350 Ω; R_T 198.70 → 421.4 Ω; I_T 120.78 → 56.96 mA; E_R3 15.373 → **19.94 V**. Counterintuitive bonus: current *through R3 rises* (43.92 → 56.96 mA) even though *total* current fell — R3 now carries all of a smaller total instead of a share of a bigger one. (This is exactly the kind of result the {↑,↓,same} table catches and gut instinct misses.)

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

**Ch. 3–4 drills (bench habits — mostly no sim needed):**

- [ ] Multimeter ritual before every session: leads in the V/Ω sockets, dial position confirmed, fuse self-test (Ω mode between the two red sockets — low Ω = good, O.L. = blown)
- [ ] Check–use–check on a 9 V battery: known source → target → known source again, until it's automatic
- [ ] Continuity feel: a jumper wire (≈0 Ω / beep) vs. the same path broken (O.L.)
- [ ] Recite the never-list until it's reflex: never Ω/continuity on a powered circuit · never turn the dial with the red lead still in the A socket · one hand for anything unknown · nothing above 30 V without a plan · no rings/watch at the bench
- [ ] Prefix sprint: 10 freehand conversions (µA↔mA, pF↔nF↔µF, kHz↔MHz, ns↔µs), then verify with the calculator in ENG mode
- [ ] Set the calculator display mode to ENG and leave it
- [ ] Falstad: hover a low-current circuit and read the values aloud in both prefix form and scientific notation until translation is instant

**Ch. 7 builds:**

- [ ] The reference circuit (24 V, 100/250 ∥ over 350/200 ∥): fill the entire E/I/R (+P) table on paper via reduce-solve-expand *first*, then hover-verify every value; confirm both KCL sums land on 120.78 mA and ΣP = P_source
- [ ] Fault drills on the same build: short R2 and check every arrow from §7.4's walkthrough; then open R4 and verify self-check #10's numbers (especially that I through R3 *rose*)
- [ ] The 7-resistor monster (§7.3): re-draw on paper with the loop-tracing method, polarity marks included; reduce symbolically right-to-left; assign your own values; predict R_T and I_T; build in Falstad and verify — this one exercise is the whole chapter
- [ ] Loaded-divider bridge to Week 2: 10k+10k on 5 V → hover V_out = 2.5 V; hang a 10k load → predict via R₂//R_load = 5k → V_out = 5·(5/15) ≈ 1.67 V, verify the sag; swap the load to 100k and watch the ≤R_load/10 rule hold (V_out ≈ 2.38 V)
- [ ] Playbook rep: pick the resistor for a 5 V / blue-LED (V_f ≈ 3.2 V) / 8 mA branch on paper (→ 225 Ω → 270 Ω standard), then build and confirm the actual current

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
- Meter contract (∞ Ω voltmeter / 0 Ω ammeter, Ω-on-dead-only, all-pairs dead checks) → **Week 3** meter work becomes procedure instead of improvisation
- Real ammeters aren't quite 0 Ω — the internal shunt drops real voltage → **Week 19** burden voltage (same tile as the §6.3 current-divider shunt)
- 30 V threshold + variable body R → standing rules for the **ebike pack & power station**: treat as dangerous, one hand, dry hands, no jewelry
- GFCI = KCL as a runtime invariant check → reinforces §6.4, and the same "current in must equal current out" reasoning finds leakage paths when debugging boards later
- Soldering iron and wall adapters are mains devices → **Week 4**: cord/plug/insulation inspection habit before every soldering session
- 4k7 / 2R2 point-free notation → **Week 20** KiCad schematics and silkscreens use it natively
- E-notation + the `M` vs. `MEG` gotcha → any move from Falstad to netlist SPICE (ngspice/LTspice)
- Sig figs & ENG display → datasheet literacy: every spec is a precision claim (typ/min/max), not an exact value
- Reduce-solve-expand → the gateway to **Thévenin/Norton equivalents** (network theorems, Vol. I Ch. 10): the ultimate "reduce" — any two-terminal mess collapses to one source + one resistor
- Loaded divider as the canonical series-parallel circuit → **Week 2** sag lab; → **Week 7** pot→ADC→PWM, where the ADC input impedance *is* the load
- Qualitative {↑,↓,same} fault tables → **Week 24** board bring-up: symptom→fault is the inverse of this chapter's fault→symptom, and forward fluency is what makes the inverse tractable
- Re-drawing convoluted schematics → **Week 20** KiCad, and the standing skill of reading vendor reference designs and datasheet application circuits (never drawn for your convenience)
- Every meter measurement creates a series-parallel circuit (voltmeter ≈∞ Ω parallels its target; ammeter ≈0 Ω inserts in series) → **Week 19** burden voltage and scope-probe loading — now computable exactly, not just hand-waved
- ≤2-wires-per-terminal + polarity-consistency etiquette → general layout hygiene and silkscreen/orientation conventions on real boards
- E-series values + design-for-tolerance → **Week 20** BOM building; the ±1%-when-it-matters judgment call returns at current-sense shunts
- Dummy 0 V sources as SPICE ammeters → ngspice/LTspice netlist debugging, where Falstad's hover doesn't exist
- Sources stack in series (4 × 6 V = 24 V) → battery pack architecture: the ebike's 36–48 V pack is series cell groups, and pack voltage math is Ch. 5 rules applied to sources
