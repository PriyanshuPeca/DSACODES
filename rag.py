```python
# main.py – In-Depth RAG Chatbot Implementation

# 1. Library Imports
# ------------------
# pypdf:
#   - Used to read PDF files page by page. We extract raw text so our RAG system can index knowledge sources.
#   - Why? PDFs are a common format for reports, manuals, and documents; we need to ingest them.
# chromadb:
#   - A vector store for high-dimensional embeddings. We store and search text chunks by meaning, not keywords.
#   - Why? Vector search offers semantic matching, so "capital of France" can retrieve "Paris is the French capital".
# requests:
#   - For making HTTP requests if we extend to fetch remote documents or APIs. (Not used below but available.)
# openai.OpenAI:
#   - Client library to interact with language models via an API proxy (OpenRouter).
#   - Why? We leverage an LLM to compose answers based on retrieved context.
# sentence_transformers.CrossEncoder:
#   - A lighter model specialized to score relevance between two texts (query & document).
#   - Why? It refines initial retrieval results by reranking top candidates for quality.
from pypdf import PdfReader
import chromadb
import requests
from openai import OpenAI
from sentence_transformers import CrossEncoder

# 2. Initialize Vector Store
# --------------------------
# Create a ChromaDB client and get (or create) a collection named 'RagTutorial'.
# - A collection is a namespace isolating your project's data.
# - We need a persistent store to add embeddings and query later.
chroma_client = chromadb.Client()  # Connect to local or remote ChromaDB server
collection = chroma_client.get_or_create_collection(
    name="RagTutorial"
)

# 3. PDF Upload & Indexing Function
# ----------------------------------
def upload_pdf(file_path: str):
    """
    1. Open the PDF (binary mode).
    2. Read each page's text.
    3. Add each page as a separate document into ChromaDB.

    Why separate pages?
    - Smaller text chunks improve embedding accuracy and retrieval speed.
    - Enables pinpointing the exact page containing the answer.
    """
    with open(file_path, 'rb') as f:
        reader = PdfReader(f)
        for page_number, page in enumerate(reader.pages):
            text = page.extract_text() or ""
            # Assign a unique ID combining filename and page number
            doc_id = f"{file_path}_page{page_number}"
            # Add to the vector store; embedding happens automatically
            collection.add(
                documents=[text],
                ids=[doc_id]
            )

# 4. Index the Knowledge Base
# ----------------------------
# Call upload_pdf() once at startup to ingest your PDF into the vector store.
# If you update or add new docs, re-run this function to keep the index current.
upload_pdf("turing.pdf")

# 5. Capture User Question
# ------------------------
# Use Python's input() to prompt the user.
# This blocks execution until the user types their question.
query = input("Enter your question: ")

# 6. Query Expansion for Robust Retrieval
# ---------------------------------------
# Create paraphrased variants to cover different ways users might phrase the same intent.
# Why? Embedding-based search can miss relevant chunks if the wording is too dissimilar.
query_variants = [
    query,
    f"Explain in simple terms: {query}",
    f"Provide a detailed explanation about: {query}",
    f"Background information on: {query}",
    f"Key points regarding: {query}"
]

# 7. Initial Retrieval from ChromaDB
# ----------------------------------
# For each variant:
#   - Query ChromaDB for top N matches (n_results=2 here).
#   - We pool all retrieved passages into one list.
# Rationale:
#   - Multiple variants reduce false negatives (missing relevant text).
#   - n_results balances between recall (higher N) and speed.
all_context_chunks = []
for variant in query_variants:
    response = collection.query(
        query_texts=[variant],  # Text to convert to embedding
        n_results=2             # Number of nearest neighbors per variant
    )
    passages = response['documents'][0]
    all_context_chunks.extend(passages)

# 8. Deduplication of Retrieved Passages
# --------------------------------------
# Remove exact duplicates to avoid redundancy in downstream processing.
# Why? Feeding repeated context confuses the reranker and generator.
seen_texts = set()
unique_chunks = []
for chunk in all_context_chunks:
    if chunk not in seen_texts:
        unique_chunks.append(chunk)
        seen_texts.add(chunk)

# 9. Reranking with a Cross-Encoder
# ----------------------------------
# Instantiating a CrossEncoder to score (query, passage) pairs.
# Steps:
#   1. Pair the original query with each unique passage.
#   2. Compute relevance scores.
#   3. Sort passages by score and pick the top K (K=5).
# Why CrossEncoder?
#   - Provides fine-grained relevance beyond simple vector distances.
#   - Helps filter out semantically close but off-topic chunks.
reranker = CrossEncoder('cross-encoder/ms-marco-MiniLM-L-6-v2')
pairs = [(query, chunk) for chunk in unique_chunks]
scores = reranker.predict(pairs)
# Combine scores with chunks and sort descending
sorted_pairs = sorted(
    zip(unique_chunks, scores),
    key=lambda x: x[1],
    reverse=True
)
# Extract the top K passages for context
top_k = 5
top_docs = [doc for doc, _ in sorted_pairs[:top_k]]

# 10. Prepare LLM Client
# ----------------------
# We use OpenRouter as a proxy to any OpenAI-compatible model.
# base_url & api_key must be set in your environment or code.
client = OpenAI(
    base_url="https://openrouter.ai/api/v1",  # Proxy endpoint
    api_key="YOUR_OPENROUTER_API_KEY"
)

# 11. Construct Messages for Chat Completion
# ------------------------------------------
# We feed each retrieved chunk as a 'system' message to provide context.
# Then the final 'user' message contains the original question.
# Why roles?
#   - 'system' messages set the context for the model.
#   - 'user' message is the actual prompt the model answers.
messages = []
for chunk in top_docs:
    messages.append({
        "role": "system",
        "content": chunk
    })
# Append user's question last
messages.append({
    "role": "user",
    "content": query
})

# 12. Generate the Final Answer
# -----------------------------
# Call the chat completion endpoint with our assembled conversation.
completion = client.chat.completions.create(
    model="microsoft/mai-ds-r1:free",
    messages=messages
)

# 13. Output the Answer
# ---------------------
# Print the model's response to the console.
# This includes the generated text, which should cite or reflect the provided context.
print("\n--- RAG-Based Answer ---")
print(completion.choices[0].message.content)
```
