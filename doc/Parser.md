# Parser
## 上下文无关文法 (context-free grammar)
$$
\begin{align}
    type & \to \textbf{int} \; | \; \textbf{char} \; | \; \textbf{float} \; | \; \textbf{string} \\
    idList & \to id\; |\; id\textbf{,}\; idList\\
    varDef & \to type\; idList \\
    varDefArgs & \to type\;id\;|\;type\;id\textbf{,}\;varDefArgs\\
    value & \to intValue\;|\;charValue\;|\;floatValue\;|\;stringValue\;|\;id\;|\;code\\
    add & \to value 
    func & \to \textbf{fn} \; type\; (varDefArgs)\;codes\\
\end{align}
$$