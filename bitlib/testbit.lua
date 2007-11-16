require "bit"
local maxbits = 32

assert (bit.band (0,0) == 0)
assert (bit.band (0,-1) == 0)
assert (bit.band (-1,-1) == -1)

assert (bit.bor  (0,0) == 0)
assert (bit.bor  (0,-1) == -1)
assert (bit.bor  (-1,-1) == -1)

assert (bit.bxor (0,0) == 0)
assert (bit.bxor (0,-1) == -1)
assert (bit.bxor (-1,-1) == 0)

assert (bit.bnot (0) == -1)
assert (bit.bnot (-1) == 0)

assert (bit.lshift (0,0) == 0)
assert (bit.lshift (-1,0) == -1)

assert (bit.rshift (0,0) == 0)
assert (bit.rshift (-1,0) == -1)

for nb = 1, maxbits do
  local a = 2 ^ nb - 1
  assert (bit.band (a,0)  == 0)
  assert (bit.band (a,1)  == 1)
  assert (bit.band (a,-1) == bit.cast (a))
  assert (bit.band (a,a)  == bit.cast (a))

  assert (bit.bor (a,0)  == bit.cast (a))
  assert (bit.bor (a,1)  == bit.cast (a))
  assert (bit.bor (a,-1) == -1)
  assert (bit.bor (a,a)  == bit.cast (a))

  assert (bit.bxor (a,0)  == bit.cast (a))
  assert (bit.bxor (a,1)  == bit.cast (a - 1))
  assert (bit.bxor (a,-1) == bit.cast (-a - 1))
  assert (bit.bxor (a,a)  == 0)

  assert (bit.bnot (a) == bit.cast (-1 - a))

  assert (bit.lshift (a, 1) == bit.cast (a + a))
  if nb < maxbits then
    assert (bit.lshift (1, nb) == bit.cast (2 ^ nb))
  end

  assert (bit.rshift (a, 1) == math.floor (a / 2))
  if nb < maxbits then
    assert (bit.rshift (a, nb) == 0)
  end
  assert (bit.rshift (a, nb - 1) == 1)
end

print "All bitlib tests passed"
