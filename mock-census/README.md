CS 142 Mid-Term 2 (Fall 2010)
====

**Mock Census Parser**

Must read a file via HTTP or on the local filesystem.

(The file has ostensibly just passed validation and needs no further error-checking)

The file contains three newline-delimited directives per block and one EOF directive.

Each directive has a number of space-delimited attributes.

The directives appear in this order:

 * `Head` - this must be the start of the block. Represents the head of household
   * name - first name of the individual
   * gender
   * eye_color
   * hair_color
   * height - feet as a float

 * `Depedent` - 0 or many may exist. Represents children, spouse, etc
   * name
   * gender
   * age - 'minor' or 'adult'
   * height

 * `End` - must close the block before the next 'Head'

 * `SUPER-END` - a special end-of-file (EOF) marker
   * `end` MUST precede `SUPER-END`

Example Data File
====

    Head Kevin M brown brown 6.15
    Dependent Dagmar F adult 5.9
    Dependent Dorkus M minor 5.7
    End
    Head Eve F blue brown 5.5
    Dependent Adam M adult 6.2
    Dependent Fred M minor 6.1
    Dependent Fredwenda F adult 5.3
    End
    Head Pentultimus M brown brown 6
    End
    Head Beautisha F green red 5.7
    Dependent Bodacious M minor 4.0
    End
    SUPER-END

Variations from the Spec
====

My implementation is written in JavaScript (which is like LISP, not at all like Java).
I take advantage of some JavaScript-isms.

In my implementation I also handle `#` comments as well as some extremely minimalistic error-checking.
