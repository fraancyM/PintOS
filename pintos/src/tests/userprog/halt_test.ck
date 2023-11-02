# -*- perl -*-
use strict;
use warnings;
use tests::tests;

our ($test);
my (@output) = read_text_file ("$test.output");

common_checks ("run", @output);

# Verifico se nel risultato del test è presente il messaggio
fail "missing 'begin' message\n"
  if !grep ($_ eq '(halt_test) begin', @output);
fail "found 'fail' message--halt didn't really halt\n"
  if grep ($_ eq '(halt_test) fail', @output);
pass "Syscall halt funzionante!\n"
  if !grep ($_ eq '(halt_test) Dopo la chiamata a sys_halt', @output);

