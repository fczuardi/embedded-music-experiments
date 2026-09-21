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
| Hold / latch | interação e voz | Koala e Roland P-6 | nenhum experimento dedicado | referência |
| Loop / toggle | política de reprodução | Koala e Roland P-6 | nenhum experimento dedicado | referência |
| Choke | política entre vozes | samplers e hi-hats de drum machines | ainda não testado | referência |
| Monofonia / polifonia | alocação de vozes | MIDI, AMY e Roland P-6 | instrumento monofônico e slot AMY | adotado localmente |
| Mute / mute all | política de pista | sequenciadores e Roland P-6 | interação planejada para Calculator | candidato |
| Pattern / section | composição | sequenciadores e Roland P-6 | seções planejadas para Calculator | candidato |
| Velocity / accent | evento e step | MIDI, Koala e Roland P-6 | velocity nos contratos e showcases MIDI | extraído para notas; candidato para steps |
| Gate time | step e voz | Roland P-6 | ainda não necessário para bateria one-shot | adiado |
| Probability | step | Roland P-6 | ainda não testado | referência |
| Micro-timing | agendamento | Roland P-6 | ainda não testado | referência |
| Sub-steps / ratchet | expansão de step | Roland P-6 | ainda não testado | referência |
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

Links e comportamentos foram verificados em 2026-09-21. Uma atualização futura
deve preservar a data e distinguir documentação oficial de inferências nossas.

## Regra de evolução

Adicionar um item ao radar requer uma fonte ou observação reproduzível. Torná-lo
uma prioridade exige um experimento concreto. Transformá-lo em contrato
compartilhado exige consumidores reais suficientes para revelar o que permanece
estável entre eles.
