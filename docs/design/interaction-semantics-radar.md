# Radar de semânticas de interação musical

**Status:** pesquisa de design, não API nem roadmap

**Última revisão:** 2026-09-21

## Propósito

Este radar guarda comportamentos encontrados em instrumentos e softwares
musicais para ajudar a nomear futuras fronteiras do ecossistema. Ele evita tanto
reinventar vocabulário estabelecido quanto transformar a primeira implementação
útil numa abstração compartilhada cedo demais.

As referências externas mostram possibilidades, não requisitos. A promoção de
um conceito continua exigindo experimentos nossos e, para uma biblioteca
compartilhada, pelo menos dois consumidores que revelem um contrato estável.

## Estados

| Estado | Significado |
| --- | --- |
| Referência | comportamento documentado em outro instrumento ou software |
| Observado | comportamento exercitado em um experimento nosso |
| Candidato | possibilidade relevante para um próximo experimento concreto |
| Adotado | semântica deliberadamente usada por uma composição local |
| Extraído | contrato promovido para pacote compartilhado |
| Adiado | possibilidade preservada sem prioridade atual |

Um conceito pode aparecer em mais de uma camada e ter estados diferentes. Por
exemplo, trigger já é uma prática observada no probe de bateria AMY, mas ainda
não foi extraído como contrato compartilhado.

## Radar atual

| Conceito | Camada provável | Referências externas | Evidência ou uso nosso | Estado atual |
| --- | --- | --- | --- | --- |
| Trigger / one-shot | evento e reprodução | Koala, Roland P-6, Pocket Operators, drum machines | probe do drum kit AMY; plano do sequenciador Calculator | observado, candidato |
| Gate | evento e voz | MIDI, Koala, Roland P-6 | Note On/Off nos showcases BLE MIDI | observado |
| Hold / latch | interação e voz | Koala, Roland P-6 e Behringer Crave | nenhum experimento dedicado | referência |
| Loop / toggle | política de reprodução | Koala e Roland P-6 | nenhum experimento dedicado | referência |
| Choke | política entre vozes | samplers e hi-hats de drum machines | ainda não testado | referência |
| Monofonia / polifonia | alocação de vozes | MIDI, AMY e Roland P-6 | instrumento monofônico e slot AMY | adotado localmente |
| Mute / mute all | política de pista | sequenciadores e Roland P-6 | interação planejada para Calculator | candidato |
| Pattern / section | composição | sequenciadores e Roland P-6 | seções planejadas para Calculator | candidato |
| Note / rest | conteúdo do step | Behringer Crave e sequenciadores melódicos | Calculator planeja trigger/rest sem pitch | referência |
| Velocity / accent | evento e step | MIDI, Koala, Roland P-6 e Behringer Crave | velocity nos contratos e showcases MIDI | extraído para notas; candidato para steps |
| Gate time | step e voz | Roland P-6 e Behringer Crave | ainda não necessário para bateria one-shot | adiado |
| Probability | step | Roland P-6 | ainda não testado | referência |
| Micro-timing | agendamento | Roland P-6 | ainda não testado | referência |
| Sub-steps / ratchet | expansão de step | Roland P-6 e Behringer Crave | ainda não testado | referência |
| Motion | automação de parâmetros | Roland P-6 | CC contínuo existe, mas não é sequenciado | referência |
| Parameter lock | automação por step | Pocket Operators | ainda não testado | referência |
| Punch-in effect | performance temporária | Pocket Operators | ainda não testado | referência |
| Accent | expressão do step | Pocket Operators e drum machines | velocity existe, accent por step ainda não | candidato distante |
| Swing | clock e agendamento | Pocket Operators, Roland P-6 e Korg Volca | tempo fixo planejado para Calculator | referência |
| Step Loop / Scatter | performance sobre transporte | Roland P-6 | ainda não testado | referência |
| Active Step | geometria do pattern | Korg Volca | todos os 16 steps planejados permanecem ativos | referência |
| Step Jump | performance sobre transporte | Korg Volca | troca de seção planejada é quantizada, não um jump | referência |
| Flux / gravação livre | captura temporal | Korg Volca Keys | ainda não testado | referência |
| Step Trigger | articulação da voz | Korg Volca Keys | ainda não testado | referência |
| Stutter | repetição performática | Korg Volca Beats | ainda não testado | referência |
| Pattern end / logical length | estrutura do pattern | Behringer Crave | Calculator planeja 16 steps fixos | referência |
| Page | navegação de edição | Behringer Crave | Calculator expõe os 16 steps simultaneamente | referência |
| Reset / hold playhead | performance sobre transporte | Behringer Crave | ainda não testado | referência |
| Arpeggiator traversal | geração algorítmica | Behringer Crave | ainda não testado | referência |
| Composition hierarchy | arranjo e armazenamento | Teenage Engineering EP-133 K.O. II | Calculator combina tracks diretamente em sections | referência |
| Commit / variation | workflow de composição | Teenage Engineering EP-133 K.O. II | ainda não testado | referência |
| Scene duration policy | sincronização de patterns | Teenage Engineering EP-133 K.O. II | sections atuais teriam duração uniforme | referência |
| Parameter scope | estado e automação | Teenage Engineering EP-133 K.O. II | ainda não formalizado | referência |
| Retrigger / legato continuation | articulação da voz | Teenage Engineering EP-133 K.O. II | synth BLE usa retrigger monofônico | referência |
| Selective quantization | edição temporal | Teenage Engineering EP-133 K.O. II | ainda não testado | referência |
| Undo | edição | Teenage Engineering EP-133 K.O. II e Pocket Operators | ainda não planejado | referência |
| Loop window | performance sobre timeline | Teenage Engineering EP-133 K.O. II | ainda não testado | referência |
| Quantized command | agendamento de interação | Teenage Engineering EP-133 K.O. II | troca de section planejada para a fronteira | candidato |
| Pressure-sensitive effect | expressão de performance | Teenage Engineering EP-133 K.O. II | hardware Calculator não mede pressão | referência |
| Tracker hierarchy | composição por referências | picoTracker e MicroDexed Touch | ainda não testado | referência |
| Command table | automação reutilizável | picoTracker | ainda não testado | referência |
| Overdub checkpoint | gravação incremental | Wavy Industries Monkey | ainda não testado | referência |
| Nondestructive modifier / mixdown | edição e renderização MIDI | RetroKits RK-008 | ainda não testado | referência |
| Track / MIDI-channel independence | roteamento | RetroKits RK-008 | canais selecionam patches AMY, mas não tracks | referência |
| Parallel sequencer models | composição | MicroDexed Touch | ainda não testado | referência |
| Conditional / generative step | decisão do sequenciador | Woovebox | ainda não testado | referência |
| Gesture mapping | expressão de performance | Donner MEDO | ainda não testado | referência |
| Pattern chain | arranjo | Pocket Operators | seções navegáveis planejadas, mas não encadeadas | referência |
| Chop | material sonoro e mapeamento | Roland P-6 | ainda não testado | referência |
| Resampling | criação de material | Koala e Roland P-6 | ainda não testado | referência |
| Síntese granular | engine sonora | Roland P-6 | AMY é outra classe de engine | referência |
| Clock / transport | tempo e execução | MIDI e sequenciadores | clock contínuo planejado para Calculator | candidato |
| Program / bank | seleção de sons | MIDI e instrumentos digitais | patches AMY selecionados por canal | referência; sem contrato próprio |

## Fronteiras sugeridas pela comparação

Os produtos estudados reforçam que o gesto, o evento e a reprodução não são a
mesma coisa:

```text
controle físico -> edição ou performance -> evento musical -> política da voz
                                               |
sequenciador -> decisão temporal ---------------+
```

- **Trigger** informa que algo deve começar agora. A duração pode ser autônoma,
  como num sample one-shot ou numa voz de bateria.
- **Gate** possui começo e fim significativos. O release pode encerrar a voz ou
  iniciar a fase de release do envelope.
- **Hold, latch e toggle** convertem um gesto momentâneo em estado persistente.
- **Loop, choke, envelope e polifonia** são políticas do instrumento ou da voz;
  não precisam inflar o evento de trigger.
- **Probability, micro-timing, sub-steps e motion** enriquecem decisões do
  sequenciador; não são propriedades obrigatórias de todo evento musical.

Por isso, um possível `TriggerEvent` deve permanecer diferente de Note On/Off.
O MIDI pode transportar bateria através de Note On, mas isso não obriga a
composição interna a fingir que todo disparo possui um release musicalmente
relevante.

## Consequência para a Calculator Face

O painel original da Calculator Face entrega eventos orientados ao release.
Essa limitação impede uma execução gate fiel pelas teclas da Face, mas combina
bem com edição de steps, disparos one-shot e comandos toggle. Os botões A, B e C
do Core Gray continuam disponíveis quando uma interação precisar distinguir
press e release.

O primeiro sequenciador de bateria deve começar com steps booleanos e triggers
one-shot. Velocity/accent, probability, sub-steps e micro-timing permanecem no
radar, sem aumentar o primeiro modelo antes de existir validação musical e de
interface para cada recurso.

## Pocket Operators como família

Os Pocket Operators são especialmente próximos da Calculator Face por obterem
vários papéis de uma grade de dezesseis teclas e poucos controles auxiliares.
Ainda assim, a família não define um único instrumento ou contrato. O núcleo
recorrente é um pattern de dezesseis steps, seleção de som, modo de escrita,
gravação ao vivo quantizada, swing, parameter locks, efeitos performáticos e
encadeamento de patterns. As especializações mudam a semântica dessa superfície:

- o **PO-32 tonic** trata a grade como sons, steps ou efeitos conforme o modo;
  oferece accent, step multiplier, mute/solo, parameter locks, efeitos punch-in
  e chains de até 64 patterns;
- o **PO-33 K.O!** separa slots melódicos, nos quais as teclas transpõem o sample
  inteiro, de slots de bateria, nos quais as teclas selecionam slices; start e
  duração podem ser editados por slice;
- o **PO-20 arcade** acrescenta seleção e chaining de acordes, além de pattern
  chaining e step multiplier, mostrando que uma segunda sequência pode dirigir
  contexto harmônico em vez de triggers de bateria.

Essa variedade reforça duas ideias para o nosso design. Primeiro, a grade física
é uma superfície modal: seu significado pertence ao estado da composição, não
ao driver do teclado. Segundo, pattern chain, parameter lock, multiplier e
punch-in effect são operações diferentes, embora compartilhem as mesmas teclas.
Não devemos reuni-las num contrato genérico apenas por terem interface física
parecida.

## Korg Volca como família

Os Volcas acrescentam principalmente operações performáticas sobre a geometria
e a posição temporal do pattern. Assim como nos Pocket Operators, recursos
variam entre modelos e não formam uma única API de sequenciador.

- **Active Step** desativa posições que passam a ser puladas durante playback e
  gravação. Isso é diferente de um rest: o rest ocupa tempo sem disparar, enquanto
  um step inativo deixa de participar do ciclo.
- **Step Jump** desloca imediatamente o playhead para uma posição pressionada.
  Isso é diferente da troca de seção quantizada planejada para a Calculator.
- **Flux**, no Volca Keys, grava e reproduz continuamente sem alinhar a execução
  ao início de um step. Com Flux desligado, a gravação volta a ser quantizada.
- **Step Trigger**, também no Volca Keys, força o envelope a reiniciar no começo
  do step. A articulação pode, portanto, ser controlada separadamente da nota.
- **Stutter**, no Volca Beats, repete o trigger de uma parte com intervalo e
  decaimento ajustáveis. Ele ocupa uma fronteira diferente do step multiplier:
  é uma transformação performática, embora ambos possam produzir repetições.
- **Choke configurável**, no Volca Drum, determina quais partes interrompem umas
  às outras e reforça choke como política entre vozes.
- **Sync por pulso** permite que um pulso externo avance um step, exemplificando
  um clock mínimo que não precisa carregar notas nem o protocolo MIDI completo.

A distinção introduzida por Active Step pode ser representada conceitualmente
por três estados, sem sugerir que o primeiro sequenciador deva implementá-los:

```text
inactive -> posição removida do ciclo
rest     -> posição consome tempo sem disparar
trigger  -> posição consome tempo e dispara
```

Flux revela outra fronteira potencial: captura quantizada produz naturalmente
um pattern de steps, enquanto captura livre exige uma timeline ou timestamps.
Essa diferença deve permanecer no radar até algum experimento nosso precisar
gravar performance, pois o sequenciador Calculator inicialmente só edita steps.

## Behringer Crave e o step melódico

O Crave complementa as drum machines ao mostrar o conteúdo necessário para
sequenciar uma voz melódica monofônica. Seu sequenciador armazena notas e rests
em patterns de até 32 steps, organizados visualmente em quatro páginas, e permite
ajustar gate length, accent, ratchet e o fim lógico do pattern.

Um step de bateria one-shot pode inicialmente responder apenas se deve disparar
uma pista. Um step melódico precisa separar mais dimensões:

```text
posição temporal
  -> note ou rest
  -> pitch, quando for note
  -> gate length
  -> accent
  -> ratchet
```

Isso não justifica uma estrutura `Step` universal. Pelo contrário, sugere que um
futuro pattern reutilizável precisaria ser parametrizado pelo tipo de conteúdo,
ou que `DrumStep` e `MonophonicNoteStep` deveriam permanecer modelos distintos.
A decisão deve esperar os dois consumidores existirem.

O Crave também ajuda a separar conceitos que uma interface compacta aproxima:

- **page** escolhe qual parte de um pattern longo está visível para edição;
- **pattern end** define seu comprimento musical lógico;
- **bank/pattern** seleciona material armazenado;
- **reset** volta imediatamente ao primeiro step;
- **hold step** mantém temporariamente a posição atual;
- **arpeggiator** gera uma ordem algorítmica a partir de notas mantidas, em vez
  de simplesmente reproduzir notas previamente gravadas no pattern.

As saídas físicas separadas de keyboard CV e gate reforçam ainda que pitch e
articulação são dimensões independentes. Um pitch pode permanecer estável
enquanto novos gates rearticulam a voz; um rest pode fechar o gate sem precisar
apagar o último pitch.

Glide/portamento existe no sintetizador, mas a documentação consultada não é
suficiente para afirmar `tie` ou slide programável por step. Esses comportamentos
não entram no radar como capacidades confirmadas do sequenciador Crave.

## Teenage Engineering EP-133 K.O. II

O K.O. II acrescenta uma hierarquia de composição mais explícita que os
instrumentos anteriores:

```text
project
  -> quatro groups com samples e patterns próprios
  -> scenes que combinam os patterns correntes
  -> song positions que referenciam scenes em ordem
```

Essa hierarquia distingue dados musicais de suas combinações. Uma scene pode
referenciar patterns de groups diferentes; uma song position referencia a scene
em vez de copiar novamente seu conteúdo. A duração da song position segue o
pattern mais longo da scene, tornando a política de duração parte explícita do
arranjo.

O comando **commit** preserva a combinação atual como scene e cria uma nova
variação baseada nela sem parar a música. Ele funciona como checkpoint criativo
e duplicate-and-continue, não apenas como persistência em armazenamento.

O K.O. II também torna explícito o escopo dos parâmetros. Volume de group no
project, level automatizável no pattern, configuração do sample, send de efeito
por group e processamento master possuem nomes parecidos, mas ciclos de vida e
capacidades de automação diferentes. Uma futura API não deveria oferecer um
`setVolume()` ambíguo sem identificar seu alvo e escopo.

Os modos de sample separam outras políticas de voz:

- **oneshot** é monofônico e toca o sample inteiro;
- **key** permite múltiplas instâncias polifônicas do mesmo sample;
- **legato** é monofônico e muda a nota preservando a posição de reprodução.

Legato demonstra que uma nova nota não precisa reiniciar cursor e articulação.
Retrigger ou continuação pertencem à política da voz, não ao Note On isolado.

Na edição temporal, o aparelho diferencia captura quantizada, free time,
correção seletiva de uma nota ou pad, deslocamento dentro ou fora da grade e
undo. Quantização aparece assim como transformação com escopo, e não apenas
configuração global do clock.

Automação de fader gravada num step é latching: o valor permanece até ser
substituído. Punch-in effects respondem à pressão e podem ser combinados. O modo
Loop possui posição e comprimento próprios e permite saída imediata ou na
próxima barra. Essa última escolha exemplifica um **quantized command**: o gesto
ocorre agora, mas a mudança de estado é aplicada numa fronteira musical.

Para a Calculator, `queue next section` já é um candidato local dessa semântica.
Isso não exige adotar a hierarquia completa do K.O. II: a primeira section pode
continuar contendo diretamente quatro tracks de dezesseis steps.

## Survey de tiny sequencers

O vídeo *Tiny Sequencers Compared*, de Floyd Steinberg, foi usado como índice de
descoberta para uma família mais ampla de instrumentos compactos. Afirmações
técnicas abaixo foram confirmadas, quando possível, nos manuais e páginas dos
respectivos projetos; o vídeo não é tratado como especificação.

### Wavy Industries Monkey: loop por overdubs

O Monkey favorece captura imediata em vez de edição de uma grade. Seu loop
recorder possui comprimento fixo de 16 beats e cria um checkpoint ao terminar
cada overdub. Undo remove o último checkpoint; uma ação mais ampla apaga um canal
MIDI inteiro. Mute por canal permite transformar as camadas gravadas num arranjo
performático simples.

Esse modelo separa `take/overdub` de `track`: o histórico de criação é composto
por passagens de gravação, enquanto organização e mute usam canais MIDI. Também
mostra uma política útil de deduplicação ao atravessar a fronteira do loop: notas
periódicas idênticas sobrepostas não são gravadas novamente.

### picoTracker: referências e comandos verticais

O picoTracker usa a hierarquia clássica de tracker: song channels referenciam
chains, chains referenciam phrases e phrases armazenam eventos em rows. Uma
chain pode reutilizar a mesma phrase com transposição diferente, reduzindo cópia
de dados musicais.

Tables formam pequenas sequências reutilizáveis de comandos, disparadas por uma
phrase ou instrumento. Elas podem executar automação, arpejos e efeitos, fazer
loop ou saltar entre trechos. Isso sugere uma fronteira entre conteúdo musical e
programas de modificação, mas não exige uma linguagem de comandos no nosso
sequenciador.

### RetroKits RK-008: performance MIDI transformável

O RK-008 grava performance MIDI em tempo real. Uma track pode conter eventos de
qualquer um dos 16 canais, e canal de saída e porta são decisões de roteamento
separadas. Track, canal MIDI e instrumento não são, portanto, sinônimos.

Volume, transpose, quantize e note length podem ser aplicados como modificadores
não destrutivos. `Mixdown` materializa essas transformações nos eventos, após o
que novas transformações podem ser empilhadas. `Merge` combina tracks ou parts;
`explode` divide conteúdo MIDI em várias tracks. O comprimento de uma part pode
ser inferido da performance gravada em vez de definido antes da captura.

Esse workflow distingue claramente:

```text
eventos gravados -> transformação não destrutiva -> render/mixdown
```

### MicroDexed Touch: dois sequenciadores sincronizados

O MicroDexed Touch mantém dois modelos que podem funcionar simultaneamente: um
sequenciador inspirado em LSDJ, estruturado em song, chains e patterns, e um
LiveSequencer voltado à gravação mais direta. A coexistência é evidência de que
tracker e gravador linear atendem atividades diferentes e não precisam ser
fundidos numa abstração única para compartilhar clock e engines sonoras.

Seu sequenciador por patterns também permite reutilizar dados com instrumentos
e transposições diferentes. O conteúdo musical pode ser uma referência
independente da voz que o executará.

### Woovebox: steps como pequenas decisões

O Woovebox amplia o step com conditionals, probability e mais de cem tipos de
modificadores, além de polirritmia, geração, randomização de patterns/chains e
transformações por fragmento no song mode. Ele representa o extremo oposto do
step booleano inicial da Calculator: cada posição pode funcionar como uma
pequena decisão programável.

Essa referência reforça a cautela do radar. Um modelo poderoso de `Step` não é
automaticamente um bom contrato comum; complexidade deve aparecer apenas quando
um experimento musical precisar dela.

### Donner MEDO: looper modal e gestos

O MEDO organiza performance em papéis como drum, bass, chord, lead e sample e
usa um looper com overdub, quantização e até 128 bars. Sensores permitem mapear
click, press, slide, slap, tilt, shake, wiggle e movimento para parâmetros.

Sua contribuição principal ao radar é a separação entre evento discreto e gesto
contínuo ou corporal. `Gesture mapping` pertence à borda de controle; o resultado
pode virar nota, modulação ou comando sem exigir que o instrumento conheça o
sensor físico.

### Itens que não entram como sequenciadores

O computador Elecrow com Raspberry Pi é uma plataforma geral capaz de hospedar
software musical, não uma semântica própria de sequenciamento. Geonkick, Surge
XT, ZynAddSubFX e TAL Noisemaker aparecem no setup como engines ou instrumentos
de software. Eles podem alimentar outra pesquisa sobre síntese e áudio, mas não
são usados como evidência deste survey de workflows.

## Referências verificadas

- [Koala Sampler Manual — Sample tab](https://manual.koalasampler.com/mobile/4-sample/):
  one-shot, gate por duração do toque, loop/hold, envelope e choke.
- [Roland P-6 — Understanding samples](https://static.roland.com/manuals/p-6/en-US/112809355114018187.html):
  configurações por sample, incluindo gate/one-shot, loop e mono/polifonia.
- [Roland P-6 — Recording with the pattern sequencer](https://static.roland.com/manuals/p-6/en-US/112170507114050443.html):
  pitch, velocity, probability, gate time, micro-timing, sub-steps e motion.
- [Roland P-6 — product overview](https://www.roland.com/us/products/p-6/):
  chop, step sampling, resampling, sequenciador de 64 steps, Step Loop e síntese
  granular.
- [Teenage Engineering PO-32 tonic guide](https://teenage.engineering/guides/po-32/en):
  grade de 16 steps, accent, parameter locks, step multiplier, mute/solo,
  punch-in effects e pattern chaining.
- [Teenage Engineering PO-33 K.O! guide](https://teenage.engineering/guides/po-33/en):
  slots melódicos e de bateria, slices, trim, parameter locks e pattern chaining.
- [Teenage Engineering PO-20 arcade guide](https://teenage.engineering/guides/po-20/en):
  chord control e chaining, parameter locks, step multiplier, efeitos e pattern
  chaining.
- [Korg Volca Beats Owner's Manual](https://cdn.korg.com/us/support/download/files/faa5792adfeaf04839e7abbf1c321acf.pdf):
  Active Step, Step Jump, Stutter, motion recording e sync por pulso.
- [Korg Volca Keys Owner's Manual](https://cdn.korg.com/us/support/download/files/93f9f953416733d196f8d817bb3bc668.pdf):
  Flux, gravação quantizada e Step Trigger.
- [Korg Volca Drum Owner's Manual](https://cdn.korg.com/us/support/download/files/ce079f2162680b4a105c85de32c00e6f.pdf):
  choke configurável por parte.
- [Korg Volca Sample overview](https://www.korg.com/us/products/dj/volca_sample/index.php):
  Active Step, Step Jump, swing e motion sequencing.
- [Behringer Crave Quick Start Guide](https://mediadl.musictribe.com/download/documents/behringer/CRAVE/CRAVE_QSG_WW.pdf):
  notes/rests, gate length, accent, ratchet, pages, pattern end, reset, hold,
  arpeggiador e saídas CV/gate.
- [Behringer Crave product overview](https://www.behringer.com/en/products/0718-AAJ):
  sequenciador de 32 steps, 64 patterns em oito bancos e oito ordens de
  arpeggiador.
- [Teenage Engineering EP-133 workflow](https://teenage.engineering/guides/ep-133/workflow):
  projects, groups, patterns, scenes, song positions e commit.
- [Teenage Engineering EP-133 sound modes](https://teenage.engineering/guides/ep-133/modes):
  oneshot, key, legato, trim e envelope.
- [Teenage Engineering EP-133 play and record](https://teenage.engineering/guides/ep-133/play-and-record):
  automação latching, escopo de volume, erase, undo e offsets temporais.
- [Teenage Engineering EP-133 functions](https://teenage.engineering/guides/ep-133/functions):
  quantização seletiva, free time, note repeat e loop window.
- [Teenage Engineering EP-133 effects](https://teenage.engineering/guides/ep-133/effects):
  effects por group e punch-in effects combináveis sensíveis à pressão.
- [Floyd Steinberg — Tiny Sequencers Compared](https://www.youtube.com/watch?v=NyjVV-oM45Q):
  índice comparativo usado para descobrir os dispositivos deste survey.
- [Wavy Industries Monkey manual](https://wavyindustries.com/monkey/manual/):
  loop de 16 beats, overdub checkpoints, undo e mute/erase por canal MIDI.
- [picoTracker manual — introduction](https://manual.xiphonics.com/advance/introduction.html),
  [chains](https://manual.xiphonics.com/advance/chains.html) e
  [tables](https://manual.xiphonics.com/advance/tables.html): tracker de oito
  canais, chains de phrases e sequências reutilizáveis de comandos.
- [RetroKits RK-008 manual](https://retrokits.com/rk008/RK008_manual.pdf):
  gravação MIDI em tempo real, routing por track, modificadores não destrutivos,
  mixdown, merge e explode.
- [MicroDexed Touch project](https://codeberg.org/positionhigh/MicroDexed-touch)
  e [manual](https://www.musikandmore.net/wp-content/uploads/2025/12/MicroDexed-touch-manual.pdf):
  sequenciadores tracker/pattern e live executáveis em paralelo.
- [Woovebox product documentation](https://www.woovebox.com/): conditionals,
  modifiers, probability, polyrhythm, generation, randomization e song mode.
- [Donner MEDO product documentation](https://www.donnermusic.com/products/medo)
  e [manual](https://cdn.accentuate.io/15091455787394/1757424260901/MEDO_maunal.pdf?v=1757424260901):
  looper, modos instrumentais, quantização e controles por gesto.

Links e comportamentos foram verificados em 2026-09-21. Uma atualização futura
deve preservar a data e distinguir documentação oficial de inferências nossas.

## Regra de evolução

Adicionar um item ao radar requer uma fonte ou observação reproduzível. Torná-lo
uma prioridade exige um experimento concreto. Transformá-lo em contrato
compartilhado exige consumidores reais suficientes para revelar o que permanece
estável entre eles.
